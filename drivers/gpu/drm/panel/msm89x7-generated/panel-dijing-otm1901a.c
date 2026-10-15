// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 Kadir / General Mobile GM 5 Plus Port
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>
#include <video/mipi_display.h>

struct dijing_otm1901a {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data *supplies;
	struct gpio_desc *reset_gpio;
};

static const struct regulator_bulk_data dijing_otm1901a_supplies[] = {
	{ .supply = "vsp" },
	{ .supply = "vsn" },
};

static inline
struct dijing_otm1901a *to_dijing_otm1901a(struct drm_panel *panel)
{
	return container_of_const(panel, struct dijing_otm1901a, panel);
}

static void dijing_otm1901a_reset(struct dijing_otm1901a *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
}

static int dijing_otm1901a_on(struct dijing_otm1901a *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x19, 0x01, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x19, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1c, 0x33);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc1, 0xe8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc1, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0,
					 0x00, 0x2f, 0x00, 0x00, 0x00, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0,
					 0x00, 0x2f, 0x00, 0x00, 0x00, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x9a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0x1e);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xac);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0x06);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xdc);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0x06);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x81);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa5, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x84);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc4, 0x20);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb3, 0x1d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x92);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe9, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf3, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb4);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0xd0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x93);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x19);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x95);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x2d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x97);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x14);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x99);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x29);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd8, 0x1d, 0x1d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0xcc);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb4);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xbc);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xf7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc3,
					 0x04, 0x18, 0x04, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x81);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa5, 0x07);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x9d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x9b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x55, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc4, 0x15);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0,
					 0x00, 0x87, 0x00, 0x0a, 0x0a, 0x00,
					 0x87, 0x0a, 0x0a, 0x00, 0x87, 0x00,
					 0x0a, 0x0a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xf0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc3,
					 0x22, 0x02, 0x00, 0x00, 0x00, 0x0c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0,
					 0x00, 0x00, 0x00, 0x00, 0x03, 0x22,
					 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xd0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc0,
					 0x00, 0x00, 0x00, 0x00, 0x03, 0x22,
					 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc2,
					 0x83, 0x01, 0x00, 0x00, 0x82, 0x01,
					 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc3,
					 0x82, 0x02, 0x03, 0x00, 0x03, 0x84,
					 0x81, 0x03, 0x03, 0x00, 0x03, 0x84);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc3,
					 0x00, 0x01, 0x03, 0x00, 0x03, 0x84,
					 0x01, 0x02, 0x03, 0x00, 0x03, 0x84);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x09, 0x0a, 0x11, 0x12, 0x13, 0x14,
					 0x15, 0x16, 0x17, 0x18, 0x28, 0x28,
					 0x28, 0x28, 0x28);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x0a, 0x09, 0x14, 0x13, 0x12, 0x11,
					 0x15, 0x16, 0x17, 0x18, 0x28, 0x28,
					 0x28, 0x28, 0x28);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x1d, 0x1e, 0x1f, 0x19, 0x1a, 0x1b,
					 0x1c, 0x20, 0x21, 0x22, 0x23, 0x24,
					 0x25, 0x26, 0x27);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x01, 0x02, 0x03, 0x05, 0x06, 0x07,
					 0x04, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xd0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcc,
					 0x00, 0x00, 0x00, 0x00, 0x05, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x01, 0xfd, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xd0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xe0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xf0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcb,
					 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
					 0x77, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcd,
					 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
					 0x3f, 0x3f, 0x3f, 0x02, 0x12, 0x11,
					 0x3f, 0x04, 0x3f);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcd,
					 0x06, 0x3f, 0x3f, 0x26, 0x26, 0x26,
					 0x21, 0x20, 0x1f, 0x26, 0x26);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xa0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcd,
					 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
					 0x3f, 0x3f, 0x3f, 0x01, 0x12, 0x11,
					 0x3f, 0x03, 0x3f);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xb0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xcd,
					 0x05, 0x3f, 0x3f, 0x26, 0x26, 0x26,
					 0x21, 0x20, 0x1f, 0x26, 0x26);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe1,
					 0x30, 0x35, 0x36, 0x3a, 0x40, 0x44,
					 0x46, 0x52, 0x58, 0x66, 0x6c, 0x72,
					 0x88, 0x81, 0x77, 0x60, 0x4d, 0x39,
					 0x2c, 0x24, 0x12, 0x09, 0x06, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe2,
					 0x30, 0x35, 0x36, 0x3a, 0x40, 0x44,
					 0x46, 0x52, 0x58, 0x66, 0x6c, 0x72,
					 0x88, 0x81, 0x77, 0x60, 0x4d, 0x39,
					 0x2c, 0x24, 0x12, 0x09, 0x06, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe3,
					 0x1c, 0x1d, 0x20, 0x25, 0x28, 0x2c,
					 0x36, 0x43, 0x48, 0x59, 0x63, 0x6c,
					 0x8d, 0x84, 0x7a, 0x63, 0x4d, 0x39,
					 0x2c, 0x24, 0x1d, 0x11, 0x07, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe4,
					 0x1c, 0x1d, 0x20, 0x25, 0x28, 0x2c,
					 0x36, 0x43, 0x48, 0x59, 0x63, 0x6c,
					 0x8d, 0x84, 0x7a, 0x63, 0x4d, 0x39,
					 0x2c, 0x24, 0x1d, 0x11, 0x07, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe5,
					 0x00, 0x07, 0x08, 0x0d, 0x13, 0x1b,
					 0x25, 0x36, 0x40, 0x52, 0x5f, 0x69,
					 0x8f, 0x86, 0x7b, 0x63, 0x4d, 0x39,
					 0x2c, 0x24, 0x1e, 0x0d, 0x04, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe6,
					 0x00, 0x07, 0x08, 0x0d, 0x13, 0x1b,
					 0x25, 0x36, 0x40, 0x52, 0x5f, 0x69,
					 0x8f, 0x86, 0x7b, 0x63, 0x4c, 0x38,
					 0x30, 0x20, 0x1e, 0x0d, 0x04, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x81);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa5, 0x07);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc4, 0x1a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x9b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x55, 0x50);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xf7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc3,
					 0x04, 0x16, 0x04, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xf2);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc1, 0x80, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x9d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc5, 0x77);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xf7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc3,
					 0x00, 0xff, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xf2);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xc1, 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0xd0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xf5,
					 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0xff, 0xff, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x51, 0xff);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x53, 0x20);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);

	return dsi_ctx.accum_err;
}

static int dijing_otm1901a_off(struct dijing_otm1901a *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 50);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_usleep_range(&dsi_ctx, 16000, 17000);

	return dsi_ctx.accum_err;
}

static int dijing_otm1901a_prepare(struct drm_panel *panel)
{
	struct dijing_otm1901a *ctx = to_dijing_otm1901a(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(dijing_otm1901a_supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	dijing_otm1901a_reset(ctx);

	ret = dijing_otm1901a_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(dijing_otm1901a_supplies), ctx->supplies);
		return ret;
	}

	return 0;
}

static int dijing_otm1901a_unprepare(struct drm_panel *panel)
{
	struct dijing_otm1901a *ctx = to_dijing_otm1901a(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = dijing_otm1901a_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(dijing_otm1901a_supplies), ctx->supplies);

	return 0;
}

static const struct drm_display_mode dijing_otm1901a_mode = {
	.clock = 145483,
	.hdisplay = 1080,
	.hsync_start = 1080 + 90,
	.hsync_end = 1080 + 90 + 20,
	.htotal = 1080 + 90 + 20 + 56,
	.vdisplay = 1920,
	.vsync_start = 1920 + 14,
	.vsync_end = 1920 + 14 + 2,
	.vtotal = 1920 + 14 + 2 + 10,
	.width_mm = 69,
	.height_mm = 122,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
};

static int dijing_otm1901a_get_modes(struct drm_panel *panel,
				     struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &dijing_otm1901a_mode);
}

static const struct drm_panel_funcs dijing_otm1901a_panel_funcs = {
	.prepare = dijing_otm1901a_prepare,
	.unprepare = dijing_otm1901a_unprepare,
	.get_modes = dijing_otm1901a_get_modes,
};


static int dijing_otm1901a_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct dijing_otm1901a *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct dijing_otm1901a, panel,
				   &dijing_otm1901a_panel_funcs,
				   DRM_MODE_CONNECTOR_DSI);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ret = devm_regulator_bulk_get_const(dev,
					    ARRAY_SIZE(dijing_otm1901a_supplies),
					    dijing_otm1901a_supplies,
					    &ctx->supplies);
	if (ret < 0)
		return ret;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM;

	ctx->panel.prepare_prev_first = true;

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void dijing_otm1901a_remove(struct mipi_dsi_device *dsi)
{
	struct dijing_otm1901a *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id dijing_otm1901a_of_match[] = {
	{ .compatible = "dijing,otm1901a" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, dijing_otm1901a_of_match);

static struct mipi_dsi_driver dijing_otm1901a_driver = {
	.probe = dijing_otm1901a_probe,
	.remove = dijing_otm1901a_remove,
	.driver = {
		.name = "panel-dijing-otm1901a",
		.of_match_table = dijing_otm1901a_of_match,
	},
};
module_mipi_dsi_driver(dijing_otm1901a_driver);

MODULE_AUTHOR("Kadir <kadir@localhost>");
MODULE_DESCRIPTION("DRM driver for Dijing OTM1901A 1080p video mode DSI panel");
MODULE_LICENSE("GPL");
