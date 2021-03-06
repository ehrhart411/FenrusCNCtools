/*
 * (C) Copyright 2019  -  Arjan van de Ven <arjanvandeven@gmail.com>
 *
 * This file is part of FenrusCNCtools
 *
 * SPDX-License-Identifier: GPL-3.0
 */
#ifndef __INCLUDE_GUARD_TOOLPATH_H_
#define __INCLUDE_GUARD_TOOLPATH_H_

#include <math.h>

struct segment {
    double X1, Y1, X2, Y2;
    
    /* unit vector that is orthogonal to the segment, pointing inwards */
    double oX, oY;
};

struct path {
    int count;
    int max;
    
    struct segment *segments;
};



extern struct path *alloc_path(int segments);
extern void add_segment_to_path(struct path *path, double X1, double Y1, double X2, double Y2);
extern void connect_segment_to_path(struct path *path, double X2, double Y2);
extern void close_path(struct path *path);

extern void svg_line(double X1, double Y1, double X2, double Y2, const char *color, double width);
extern void svg_circle(double X1, double Y1, double radius, const char *color, double width);
extern void set_svg_bounding_box(int X1, int Y1, int X2, int Y2);
extern void write_svg_header(const char *filename, double scale);
extern void write_svg_footer(void);
extern void make_polyvector_with_holes(void);
extern void write_svg(const char *filename);
extern void write_gcode(const char *filename);
extern void set_tool_imperial(const char *name, int nr, double diameter_inch, double stepover_inch, double maxdepth_inch, double feedrate_ipm, double plungerate_ipm);
extern void set_tool_metric(const char *name, int nr, double diameter_mm, double stepover_mm, double maxdepth_mm, double feedrate_mmpm, double plungerate_mmpm);
extern double get_tool_diameter(void);
extern double get_tool_stepover_gcode(void);
extern double get_tool_maxdepth(void);
extern void set_retract_height_imperial(double _rh_inch);
extern void set_retract_height_metric(double _rh_mm);
extern void set_rippem(double _rippem);
extern void write_gcode_header(const char *filename);
extern void write_gcode_footer(void);
extern void gcode_mill_to(double X, double Y, double Z, double speedratio);
extern void gcode_vmill_to(double X, double Y, double Z, double speedratio);
extern void gcode_plunge_to(double Z, double speedratio);
extern void gcode_retract(void);
extern void gcode_travel_to(double X, double Y);
extern void gcode_conditional_travel_to(double X, double Y, double Z, double speed);
extern void gcode_vconditional_travel_to(double X, double Y, double Z, double speed, double nextX, double nextY, double nextZ);
extern void gcode_write_comment(const char *comment);
extern double gcode_current_X(void);
extern double gcode_current_Y(void);
extern void read_tool_lib(const char *filename);
extern int have_tool(int nr);
extern void activate_tool(int nr);
extern void print_tools(void);
extern const char * tool_svgcolor(int toolnr);
extern double get_tool_stepover(int toolnr);
extern void gcode_tool_change(int toolnr);
extern double get_tool_angle(int toolnr);
extern int tool_is_vcarve(int toolnr);
extern int gcode_vconditional_would_retract(double X, double Y, double Z, double speed, double nextX, double nextY, double nextZ);
extern double distance_point_from_vector(double X1, double Y1, double X2, double Y2, double pX, double pY);
extern int lines_tangent_to_two_circles(double X1, double Y1, double R1, double X2, double Y2, double R2, int select, double *pX1, double *pY1, double *pX2, double *pY2);
extern int vector_intersects_vector(double X1, double Y1, double X2, double Y2, double X3, double Y3, double X4, double Y4, double *pX, double *pY);
extern int vector_intersects_vector_l(double X1, double Y1, double X2, double Y2, double X3, double Y3, double X4, double Y4, double *out_l);
extern void vector_apply_l(double *X1, double *Y1, double *X2, double *Y2, double l1,double l2);
extern double tool_diam(int toolnr);
extern int gcode_has_current(void);
extern void gcode_reset_current(void);

static inline double px_to_inch(double px) { return px / 96.0; };
static inline double px_to_mm(double px) { return 25.4 * px / 96.0; };
static inline double mm_to_px(double px) { return 96.0 * px / 25.4; };
static inline double inch_to_px(double inch) { return inch * 96.0; };
static inline double inch_to_mm(double inch) { return 25.4 * inch; };
static inline double mm_to_inch(double inch) { return inch / 25.4; };
static inline double ipm_to_metric(double inch) { return 25.4 * inch; };
static inline double radius_to_depth(double r, double angle) { return -r / tan(angle/360.0 * M_PI); }
static inline double depth_to_radius(double d, double angle) { return fabs(d) * tan(angle/360.0 * M_PI); }

extern int verbose;

static inline int approx3(double A, double B) { if (fabs(A-B) < 0.002) return 1; return 0; }
static inline int approx4(double A, double B) { if (fabs(A-B) < 0.0002) return 1; return 0; }
static inline int approx5(double A, double B) { if (fabs(A-B) < 0.00002) return 1; return 0; }

#define vprintf(...) do { if (verbose) printf(__VA_ARGS__); } while (0)

#endif