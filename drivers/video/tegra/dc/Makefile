GCOV_PROFILE := y
EXTRA_CFLAGS += -Idrivers/video/tegra/host
obj-y += dc.o bandwidth.o mode.o clock.o lut.o csc.o window.o
obj-y += rgb.o
obj-$(CONFIG_TEGRA_MIPI_CAL) += mipi_cal.o
ifneq ($(CONFIG_DISABLE_FB1_AND_HDMI),y)
obj-$(CONFIG_TEGRA_NVHDCP) += nvhdcp.o
obj-y += hdmi.o
endif
obj-y += edid.o
obj-y += nvsd.o
obj-y += dsi.o
obj-y += dc_sysfs.o
obj-y += dc_config.o
obj-$(CONFIG_TEGRA_DC_EXTENSIONS) += ext/
