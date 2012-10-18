/*
 * arch/arm/mach-tegra/include/mach/mc.h
 *
 * Copyright (C) 2010-2012 Google, Inc.
 *
 * Author:
 *	Erik Gilling <konkers@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __MACH_TEGRA_MC_H
#define __MACH_TEGRA_MC_H

#if defined(CONFIG_ARCH_TEGRA_2x_SOC)
#define TEGRA_MC_FPRI_CTRL_AVPC		0x17c
#define TEGRA_MC_FPRI_CTRL_DC		0x180
#define TEGRA_MC_FPRI_CTRL_DCB		0x184
#define TEGRA_MC_FPRI_CTRL_EPP		0x188
#define TEGRA_MC_FPRI_CTRL_G2		0x18c
#define TEGRA_MC_FPRI_CTRL_HC		0x190
#define TEGRA_MC_FPRI_CTRL_ISP		0x194
#define TEGRA_MC_FPRI_CTRL_MPCORE	0x198
#define TEGRA_MC_FPRI_CTRL_MPEA		0x19c
#define TEGRA_MC_FPRI_CTRL_MPEB		0x1a0
#define TEGRA_MC_FPRI_CTRL_MPEC		0x1a4
#define TEGRA_MC_FPRI_CTRL_NV		0x1a8
#define TEGRA_MC_FPRI_CTRL_PPCS		0x1ac
#define TEGRA_MC_FPRI_CTRL_VDE		0x1b0
#define TEGRA_MC_FPRI_CTRL_VI		0x1b4

#define TEGRA_MC_CLIENT_AVPCARM7R	((TEGRA_MC_FPRI_CTRL_AVPC << 8) | 0)
#define TEGRA_MC_CLIENT_AVPCARM7W	((TEGRA_MC_FPRI_CTRL_AVPC << 8) | 2)
#define TEGRA_MC_CLIENT_DISPLAY0A	((TEGRA_MC_FPRI_CTRL_DC << 8) | 0)
#define TEGRA_MC_CLIENT_DISPLAY0B	((TEGRA_MC_FPRI_CTRL_DC << 8) | 2)
#define TEGRA_MC_CLIENT_DISPLAY0C	((TEGRA_MC_FPRI_CTRL_DC << 8) | 4)
#define TEGRA_MC_CLIENT_DISPLAY1B	((TEGRA_MC_FPRI_CTRL_DC << 8) | 6)
#define TEGRA_MC_CLIENT_DISPLAYHC	((TEGRA_MC_FPRI_CTRL_DC << 8) | 8)
#define TEGRA_MC_CLIENT_DISPLAY0AB	((TEGRA_MC_FPRI_CTRL_DCB << 8) | 0)
#define TEGRA_MC_CLIENT_DISPLAY0BB	((TEGRA_MC_FPRI_CTRL_DCB << 8) | 2)
#define TEGRA_MC_CLIENT_DISPLAY0CB	((TEGRA_MC_FPRI_CTRL_DCB << 8) | 4)
#define TEGRA_MC_CLIENT_DISPLAY1BB	((TEGRA_MC_FPRI_CTRL_DCB << 8) | 6)
#define TEGRA_MC_CLIENT_DISPLAYHCB	((TEGRA_MC_FPRI_CTRL_DCB << 8) | 8)
#define TEGRA_MC_CLIENT_EPPUP		((TEGRA_MC_FPRI_CTRL_EPP << 8) | 0)
#define TEGRA_MC_CLIENT_EPPU		((TEGRA_MC_FPRI_CTRL_EPP << 8) | 2)
#define TEGRA_MC_CLIENT_EPPV		((TEGRA_MC_FPRI_CTRL_EPP << 8) | 4)
#define TEGRA_MC_CLIENT_EPPY		((TEGRA_MC_FPRI_CTRL_EPP << 8) | 6)
#define TEGRA_MC_CLIENT_G2PR		((TEGRA_MC_FPRI_CTRL_G2 << 8) | 0)
#define TEGRA_MC_CLIENT_G2SR		((TEGRA_MC_FPRI_CTRL_G2 << 8) | 2)
#define TEGRA_MC_CLIENT_G2DR		((TEGRA_MC_FPRI_CTRL_G2 << 8) | 4)
#define TEGRA_MC_CLIENT_G2DW		((TEGRA_MC_FPRI_CTRL_G2 << 8) | 6)
#define TEGRA_MC_CLIENT_HOST1XDMAR	((TEGRA_MC_FPRI_CTRL_HC << 8) | 0)
#define TEGRA_MC_CLIENT_HOST1XR		((TEGRA_MC_FPRI_CTRL_HC << 8) | 2)
#define TEGRA_MC_CLIENT_HOST1XW		((TEGRA_MC_FPRI_CTRL_HC << 8) | 4)
#define TEGRA_MC_CLIENT_ISPW		((TEGRA_MC_FPRI_CTRL_ISP << 8) | 0)
#define TEGRA_MC_CLIENT_MPCORER		((TEGRA_MC_FPRI_CTRL_MPCORE << 8) | 0)
#define TEGRA_MC_CLIENT_MPCOREW		((TEGRA_MC_FPRI_CTRL_MPCORE << 8) | 2)
#define TEGRA_MC_CLIENT_MPEAMEMRD	((TEGRA_MC_FPRI_CTRL_MPEA << 8) | 0)
#define TEGRA_MC_CLIENT_MPEUNIFBR	((TEGRA_MC_FPRI_CTRL_MPEB << 8) | 0)
#define TEGRA_MC_CLIENT_MPE_IPRED	((TEGRA_MC_FPRI_CTRL_MPEB << 8) | 2)
#define TEGRA_MC_CLIENT_MPEUNIFBW	((TEGRA_MC_FPRI_CTRL_MPEB << 8) | 4)
#define TEGRA_MC_CLIENT_MPECSRD		((TEGRA_MC_FPRI_CTRL_MPEC << 8) | 0)
#define TEGRA_MC_CLIENT_MPECSWR		((TEGRA_MC_FPRI_CTRL_MPEC << 8) | 2)
#define TEGRA_MC_CLIENT_FDCDRD		((TEGRA_MC_FPRI_CTRL_NV << 8) | 0)
#define TEGRA_MC_CLIENT_IDXSRD		((TEGRA_MC_FPRI_CTRL_NV << 8) | 2)
#define TEGRA_MC_CLIENT_TEXSRD		((TEGRA_MC_FPRI_CTRL_NV << 8) | 4)
#define TEGRA_MC_CLIENT_FDCDWR		((TEGRA_MC_FPRI_CTRL_NV << 8) | 6)
#define TEGRA_MC_CLIENT_PPCSAHBDMAR	((TEGRA_MC_FPRI_CTRL_PPCS << 8) | 0)
#define TEGRA_MC_CLIENT_PPCSAHBSLVR     ((TEGRA_MC_FPRI_CTRL_PPCS << 8) | 2)
#define TEGRA_MC_CLIENT_PPCSAHBDMAW     ((TEGRA_MC_FPRI_CTRL_PPCS << 8) | 4)
#define TEGRA_MC_CLIENT_PPCSAHBSLVW     ((TEGRA_MC_FPRI_CTRL_PPCS << 8) | 6)
#define TEGRA_MC_CLIENT_VDEBSEVR	((TEGRA_MC_FPRI_CTRL_VDE << 8) | 0)
#define TEGRA_MC_CLIENT_VDEMBER		((TEGRA_MC_FPRI_CTRL_VDE << 8) | 2)
#define TEGRA_MC_CLIENT_VDEMCER		((TEGRA_MC_FPRI_CTRL_VDE << 8) | 4)
#define TEGRA_MC_CLIENT_VDETPER		((TEGRA_MC_FPRI_CTRL_VDE << 8) | 6)
#define TEGRA_MC_CLIENT_VDEBSEVW	((TEGRA_MC_FPRI_CTRL_VDE << 8) | 8)
#define TEGRA_MC_CLIENT_VDEMBEW		((TEGRA_MC_FPRI_CTRL_VDE << 8) | 10)
#define TEGRA_MC_CLIENT_VDETPMW		((TEGRA_MC_FPRI_CTRL_VDE << 8) | 12)
#define TEGRA_MC_CLIENT_VIRUV		((TEGRA_MC_FPRI_CTRL_VI << 8) | 0)
#define TEGRA_MC_CLIENT_VIWSB		((TEGRA_MC_FPRI_CTRL_VI << 8) | 2)
#define TEGRA_MC_CLIENT_VIWU		((TEGRA_MC_FPRI_CTRL_VI << 8) | 4)
#define TEGRA_MC_CLIENT_VIWV		((TEGRA_MC_FPRI_CTRL_VI << 8) | 6)
#define TEGRA_MC_CLIENT_VIWY		((TEGRA_MC_FPRI_CTRL_VI << 8) | 8)

#define TEGRA_MC_PRIO_LOWEST		0
#define TEGRA_MC_PRIO_LOW		1
#define TEGRA_MC_PRIO_MED		2
#define TEGRA_MC_PRIO_HIGH		3
#define TEGRA_MC_PRIO_MASK		3

void tegra_mc_set_priority(unsigned long client, unsigned long prio);

#else
	/* !!!FIXME!!! IMPLEMENT ME */
#define tegra_mc_set_priority(client, prio) \
	do { /* nothing for now */ } while (0)
#endif

int tegra_mc_get_tiled_memory_bandwidth_multiplier(void);

unsigned int tegra_emc_bw_to_freq_req(unsigned int bw_kbps);

unsigned int tegra_emc_freq_req_to_bw(unsigned int freq_kbps);

/* API to get freqency switch latency at given MC freq.
 * freq_khz: Frequncy in KHz.
 * retruns latency in microseconds.
 */
static inline unsigned tegra_emc_dvfs_latency(unsigned int freq_khz)
{
	/* The latency data is not available based on freq.
	 * H/W expects it to be around 3 to 4us.
	 */
	return 4;
}

#endif
