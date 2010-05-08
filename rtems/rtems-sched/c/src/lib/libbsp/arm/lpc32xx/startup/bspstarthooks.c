/**
 * @file
 *
 * @ingroup lpc32xx
 *
 * @brief Startup code.
 */

/*
 * Copyright (c) 2009
 * embedded brains GmbH
 * Obere Lagerstr. 30
 * D-82178 Puchheim
 * Germany
 * <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <stdbool.h>

#include <bspopts.h>
#include <bsp/start.h>
#include <bsp/lpc32xx.h>
#include <bsp/mmu.h>
#include <bsp/linker-symbols.h>

#ifdef LPC32XX_DISABLE_READ_WRITE_DATA_CACHE
  #define LPC32XX_MMU_READ_WRITE_DATA LPC32XX_MMU_READ_WRITE
#else
  #define LPC32XX_MMU_READ_WRITE_DATA LPC32XX_MMU_READ_WRITE_CACHED
#endif

#ifdef LPC32XX_DISABLE_READ_ONLY_PROTECTION
  #define LPC32XX_MMU_READ_ONLY_DATA LPC32XX_MMU_READ_WRITE_CACHED
  #define LPC32XX_MMU_CODE LPC32XX_MMU_READ_WRITE_CACHED
#else
  #define LPC32XX_MMU_READ_ONLY_DATA LPC32XX_MMU_READ_ONLY_CACHED
  #define LPC32XX_MMU_CODE LPC32XX_MMU_READ_ONLY_CACHED
#endif

#define BSP_START_SECTION __attribute__((section(".bsp_start")))
#define BSP_START_DATA_SECTION __attribute__((section(".bsp_start_data")))

static void BSP_START_SECTION lpc32xx_clear_bss(void)
{
  const int *end = (const int *) bsp_section_bss_end;
  int *out = (int *) bsp_section_bss_begin;

  /* Clear BSS */
  while (out != end) {
    *out = 0;
    ++out;
  }
}

typedef struct {
  uint32_t begin;
  uint32_t end;
  uint32_t flags;
} lpc32xx_mmu_config;

static const BSP_START_DATA_SECTION lpc32xx_mmu_config
  lpc32xx_mmu_config_table [] = {
  {
    .begin = (uint32_t) bsp_section_start_begin,
    .end = (uint32_t) bsp_section_start_end,
    .flags = LPC32XX_MMU_CODE
  }, {
    .begin = (uint32_t) bsp_section_vector_begin,
    .end = (uint32_t) bsp_section_vector_end,
    .flags = LPC32XX_MMU_READ_WRITE_CACHED
  }, {
    .begin = (uint32_t) bsp_section_text_begin,
    .end = (uint32_t) bsp_section_text_end,
    .flags = LPC32XX_MMU_CODE
  }, {
    .begin = (uint32_t) bsp_section_rodata_begin,
    .end = (uint32_t) bsp_section_rodata_end,
    .flags = LPC32XX_MMU_READ_ONLY_DATA
  }, {
    .begin = (uint32_t) bsp_section_data_begin,
    .end = (uint32_t) bsp_section_data_end,
    .flags = LPC32XX_MMU_READ_WRITE_DATA
  }, {
    .begin = (uint32_t) bsp_section_fast_begin,
    .end = (uint32_t) bsp_section_fast_end,
    .flags = LPC32XX_MMU_CODE
  }, {
    .begin = (uint32_t) bsp_section_bss_begin,
    .end = (uint32_t) bsp_section_bss_end,
    .flags = LPC32XX_MMU_READ_WRITE_DATA
  }, {
    .begin = (uint32_t) bsp_section_work_begin,
    .end = (uint32_t) bsp_section_work_end,
    .flags = LPC32XX_MMU_READ_WRITE_DATA
  }, {
    .begin = (uint32_t) bsp_section_stack_begin,
    .end = (uint32_t) bsp_section_stack_end,
    .flags = LPC32XX_MMU_READ_WRITE_DATA
  }, {
    .begin = 0x0U,
    .end = 0x100000U,
    .flags = LPC32XX_MMU_READ_ONLY_CACHED
  }, {
    .begin = 0x20000000U,
    .end = 0x200c0000U,
    .flags = LPC32XX_MMU_READ_WRITE
  }, {
    .begin = 0x30000000U,
    .end = 0x32000000U,
    .flags = LPC32XX_MMU_READ_WRITE
  }, {
    .begin = 0x40000000U,
    .end = 0x40100000U,
    .flags = LPC32XX_MMU_READ_WRITE
  }
};

static void BSP_START_SECTION lpc32xx_mmu_set_entries(
  uint32_t *ttb,
  const lpc32xx_mmu_config *config
)
{
  uint32_t i = ARM_MMU_SECT_GET_INDEX(config->begin);
  uint32_t iend = ARM_MMU_SECT_GET_INDEX(ARM_MMU_SECT_MVA_ALIGN_UP(config->end));

  if (config->begin != config->end) {
    while (i < iend) {
      ttb [i] = (i << ARM_MMU_SECT_BASE_SHIFT) | config->flags;
      ++i;
    }
  }
}

static void BSP_START_SECTION lpc32xx_mmu_and_cache_setup(void)
{
  uint32_t const dac =
    ARM_CP15_DAC_DOMAIN(LPC32XX_MMU_CLIENT_DOMAIN, ARM_CP15_DAC_CLIENT);
  uint32_t ctrl = 0;
  uint32_t *const ttb = (uint32_t *) bsp_section_work_end;
  size_t const config_entry_count =
    sizeof(lpc32xx_mmu_config_table) / sizeof(lpc32xx_mmu_config_table [0]);
  size_t i = 0;

  /* Disable MMU and cache, basic settings */
  ctrl = arm_cp15_get_control();
  ctrl &= ~(ARM_CP15_CTRL_I | ARM_CP15_CTRL_R | ARM_CP15_CTRL_C
    | ARM_CP15_CTRL_V | ARM_CP15_CTRL_M);
  ctrl |= ARM_CP15_CTRL_S | ARM_CP15_CTRL_A;
  arm_cp15_set_control(ctrl);

  arm_cp15_cache_invalidate();
  arm_cp15_tlb_invalidate();

  arm_cp15_set_domain_access_control(dac);
  arm_cp15_set_translation_table_base(ttb);

  /* Initialize translation table with invalid entries */
  for (i = 0; i < ARM_MMU_TRANSLATION_TABLE_ENTRY_COUNT; ++i) {
    ttb [i] = 0;
  }

  for (i = 0; i < config_entry_count; ++i) {
    lpc32xx_mmu_set_entries(ttb, &lpc32xx_mmu_config_table [i]);
  }

  /* Enable MMU and cache */
  ctrl |= ARM_CP15_CTRL_I | ARM_CP15_CTRL_C | ARM_CP15_CTRL_M;
  arm_cp15_set_control(ctrl);
}

void BSP_START_SECTION bsp_start_hook_0(void)
{
  lpc32xx_mmu_and_cache_setup();
}

void BSP_START_SECTION bsp_start_hook_1(void)
{
  /* TODO */

  /* Copy .text section */
  arm_cp15_instruction_cache_invalidate();
  bsp_start_memcpy(
    (int *) bsp_section_text_begin,
    (const int *) bsp_section_text_load_begin,
    (size_t) bsp_section_text_size
  );

  /* Copy .rodata section */
  arm_cp15_instruction_cache_invalidate();
  bsp_start_memcpy(
    (int *) bsp_section_rodata_begin,
    (const int *) bsp_section_rodata_load_begin,
    (size_t) bsp_section_rodata_size
  );

  /* Copy .data section */
  arm_cp15_instruction_cache_invalidate();
  bsp_start_memcpy(
    (int *) bsp_section_data_begin,
    (const int *) bsp_section_data_load_begin,
    (size_t) bsp_section_data_size
  );

  /* Copy .fast section */
  arm_cp15_instruction_cache_invalidate();
  bsp_start_memcpy(
    (int *) bsp_section_fast_begin,
    (const int *) bsp_section_fast_load_begin,
    (size_t) bsp_section_fast_size
  );

  /* Clear .bss section */
  lpc32xx_clear_bss();

  /* At this point we can use objects outside the .start section */
}
