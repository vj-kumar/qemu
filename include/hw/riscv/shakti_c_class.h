/*
 * Shakti C-class machine interface
 *
 * Copyright (c) 2020, Vijai Kumar K <vijaikumar.kanagarajan@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HW_SHAKTI_C_CLASS_H
#define HW_SHAKTI_C_CLASS_H

#include "hw/net/cadence_gem.h"
#include "hw/riscv/riscv_hart.h"
#include "hw/riscv/shakti_cpu.h"
#include "hw/riscv/sifive_u_prci.h"
#include "hw/riscv/sifive_u_otp.h"

#define TYPE_RISCV_C_CLASS_SOC "riscv.shakti.cclass.soc"
#define RISCV_C_CLASS_SOC(obj) \
    OBJECT_CHECK(ShaktiCclassSocState, (obj), TYPE_RISCV_C_CLASS_SOC)

typedef struct ShaktiCclassSocState {
    /*< private >*/
    SysBusDevice parent_obj;

    /*< public >*/
    CPUClusterState e_cluster;
    CPUClusterState u_cluster;
    RISCVHartArrayState e_cpus;
    RISCVHartArrayState u_cpus;
    DeviceState *plic;
    SiFiveUPRCIState prci;
    SiFiveUOTPState otp;
    CadenceGEMState gem;

    uint32_t serial;
} ShaktiCclassSocState;

#define TYPE_RISCV_C_CLASS_MACHINE MACHINE_TYPE_NAME("shakti_c_class")
#define RISCV_C_CLASS_MACHINE(obj) \
    OBJECT_CHECK(ShaktiCclassState, (obj), TYPE_RISCV_C_CLASS_MACHINE)

typedef struct ShaktiCclassState {
    /*< private >*/
    MachineState parent_obj;

    /*< public >*/
    ShaktiCclassSoCState soc;

    void *fdt;
    int fdt_size;

    bool start_in_flash;
    uint32_t serial;
} ShaktiCclassState;

enum {
    SHAKTI_C_CLASS_DEBUG,
    SHAKTI_C_CLASS_MROM,
    SHAKTI_C_CLASS_CLINT,
    SHAKTI_C_CLASS_L2LIM,
    SHAKTI_C_CLASS_PLIC,
    SHAKTI_C_CLASS_PRCI,
    SHAKTI_C_CLASS_UART0,
    SHAKTI_C_CLASS_UART1,
    SHAKTI_C_CLASS_OTP,
    SHAKTI_C_CLASS_FLASH0,
    SHAKTI_C_CLASS_DRAM,
    SHAKTI_C_CLASS_GEM,
    SHAKTI_C_CLASS_GEM_MGMT
};

enum {
    SHAKTI_C_CLASS_UART0_IRQ = 4,
    SHAKTI_C_CLASS_UART1_IRQ = 5,
    SHAKTI_C_CLASS_GEM_IRQ = 0x35
};

enum {
    SHAKTI_C_CLASS_HFCLK_FREQ = 33333333,
    SHAKTI_C_CLASS_RTCCLK_FREQ = 1000000
};

#define SHAKTI_C_CLASS_MANAGEMENT_CPU_COUNT   1
#define SHAKTI_C_CLASS_COMPUTE_CPU_COUNT      4

#define SHAKTI_C_CLASS_PLIC_HART_CONFIG "MS"
#define SHAKTI_C_CLASS_PLIC_NUM_SOURCES 54
#define SHAKTI_C_CLASS_PLIC_NUM_PRIORITIES 7
#define SHAKTI_C_CLASS_PLIC_PRIORITY_BASE 0x04
#define SHAKTI_C_CLASS_PLIC_PENDING_BASE 0x1000
#define SHAKTI_C_CLASS_PLIC_ENABLE_BASE 0x2000
#define SHAKTI_C_CLASS_PLIC_ENABLE_STRIDE 0x80
#define SHAKTI_C_CLASS_PLIC_CONTEXT_BASE 0x200000
#define SHAKTI_C_CLASS_PLIC_CONTEXT_STRIDE 0x1000

#endif
