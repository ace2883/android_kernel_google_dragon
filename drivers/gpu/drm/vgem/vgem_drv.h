/*
 * Copyright © 2012 Intel Corporation
 * Copyright © 2014 The Chromium OS Authors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Ben Widawsky <ben@bwidawsk.net>
 *
 */

#ifndef _VGEM_DRV_H_
#define _VGEM_DRV_H_

#include <drm/drmP.h>
#include <drm/drm_gem.h>

#define DRM_VGEM_MODE_MAP_DUMB 0x00
#define DRM_IOCTL_VGEM_MODE_MAP_DUMB DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_VGEM_MODE_MAP_DUMB, struct drm_mode_map_dumb)

#define to_vgem_bo(x) container_of(x, struct drm_vgem_gem_object, base)
struct drm_vgem_gem_object {
	struct drm_gem_object base;
	struct page **pages;
	bool use_dma_buf;
};

/* vgem_drv.c */
extern void vgem_gem_put_pages(struct drm_vgem_gem_object *obj);
extern int vgem_gem_get_pages(struct drm_vgem_gem_object *obj);

/* vgem_dma_buf.c */
extern struct sg_table *vgem_gem_prime_get_sg_table(
			struct drm_gem_object *gobj);
extern int vgem_gem_prime_pin(struct drm_gem_object *gobj);
extern void vgem_gem_prime_unpin(struct drm_gem_object *gobj);
extern void *vgem_gem_prime_vmap(struct drm_gem_object *gobj);
extern void vgem_gem_prime_vunmap(struct drm_gem_object *obj, void *vaddr);
extern struct drm_gem_object *vgem_gem_prime_import(struct drm_device *dev,
						    struct dma_buf *dma_buf);

#endif
