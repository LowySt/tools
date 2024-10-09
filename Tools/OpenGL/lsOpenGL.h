#ifndef LS_OPENGL_H
#define LS_OPENGL_H

#include "win32.h"
#include "lsWindows.h"
#include "OpenGL\glCoreARB.h"
#include "OpenGL\wglExt.h"

#if 0
//NOTE: Basic OpenGL Functions from 1.3-ish that are linked using the opengl32.lib
WINGDIAPI void APIENTRY glAccum (GLenum op, GLfloat value);
WINGDIAPI void APIENTRY glAlphaFunc(GLenum func, GLclampf ref);
WINGDIAPI GLboolean APIENTRY glAreTexturesResident (GLsizei n, const GLuint *textures, GLboolean *residences);
WINGDIAPI void APIENTRY glArrayElement (GLint i);
WINGDIAPI void APIENTRY glBegin (GLenum mode);
WINGDIAPI void APIENTRY glBitmap (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
WINGDIAPI void APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
WINGDIAPI void APIENTRY glCallList (GLuint list);
WINGDIAPI void APIENTRY glCallLists (GLsizei n, GLenum type, const GLvoid *lists);
WINGDIAPI void APIENTRY glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
WINGDIAPI void APIENTRY glClearIndex (GLfloat c);
WINGDIAPI void APIENTRY glClearStencil (GLint s);
WINGDIAPI void APIENTRY glClipPlane (GLenum plane, const GLdouble *equation);
WINGDIAPI void APIENTRY glColor3b (GLbyte red, GLbyte green, GLbyte blue);
WINGDIAPI void APIENTRY glColor3bv (const GLbyte *v);
WINGDIAPI void APIENTRY glColor3d (GLdouble red, GLdouble green, GLdouble blue);
WINGDIAPI void APIENTRY glColor3dv (const GLdouble *v);
WINGDIAPI void APIENTRY glColor3f (GLfloat red, GLfloat green, GLfloat blue);
WINGDIAPI void APIENTRY glColor3fv (const GLfloat *v);
WINGDIAPI void APIENTRY glColor3i (GLint red, GLint green, GLint blue);
WINGDIAPI void APIENTRY glColor3iv (const GLint *v);
WINGDIAPI void APIENTRY glColor3s (GLshort red, GLshort green, GLshort blue);
WINGDIAPI void APIENTRY glColor3sv (const GLshort *v);
WINGDIAPI void APIENTRY glColor3ub (GLubyte red, GLubyte green, GLubyte blue);
WINGDIAPI void APIENTRY glColor3ubv (const GLubyte *v);
WINGDIAPI void APIENTRY glColor3ui (GLuint red, GLuint green, GLuint blue);
WINGDIAPI void APIENTRY glColor3uiv (const GLuint *v);
WINGDIAPI void APIENTRY glColor3us (GLushort red, GLushort green, GLushort blue);
WINGDIAPI void APIENTRY glColor3usv (const GLushort *v);
WINGDIAPI void APIENTRY glColor4b (GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
WINGDIAPI void APIENTRY glColor4bv (const GLbyte *v);
WINGDIAPI void APIENTRY glColor4d (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
WINGDIAPI void APIENTRY glColor4dv (const GLdouble *v);
WINGDIAPI void APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
WINGDIAPI void APIENTRY glColor4fv (const GLfloat *v);
WINGDIAPI void APIENTRY glColor4i (GLint red, GLint green, GLint blue, GLint alpha);
WINGDIAPI void APIENTRY glColor4iv (const GLint *v);
WINGDIAPI void APIENTRY glColor4s (GLshort red, GLshort green, GLshort blue, GLshort alpha);
WINGDIAPI void APIENTRY glColor4sv (const GLshort *v);
WINGDIAPI void APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
WINGDIAPI void APIENTRY glColor4ubv (const GLubyte *v);
WINGDIAPI void APIENTRY glColor4ui (GLuint red, GLuint green, GLuint blue, GLuint alpha);
WINGDIAPI void APIENTRY glColor4uiv (const GLuint *v);
WINGDIAPI void APIENTRY glColor4us (GLushort red, GLushort green, GLushort blue, GLushort alpha);
WINGDIAPI void APIENTRY glColor4usv (const GLushort *v);
WINGDIAPI void APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
WINGDIAPI void APIENTRY glColorMaterial (GLenum face, GLenum mode);
WINGDIAPI void APIENTRY glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
WINGDIAPI void APIENTRY glCopyPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
WINGDIAPI void APIENTRY glCopyTexImage1D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
WINGDIAPI void APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
WINGDIAPI void APIENTRY glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
WINGDIAPI void APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
WINGDIAPI void APIENTRY glCullFace (GLenum mode);
WINGDIAPI void APIENTRY glDeleteLists (GLuint list, GLsizei range);
WINGDIAPI void APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures);
WINGDIAPI void APIENTRY glDepthMask (GLboolean flag);
WINGDIAPI void APIENTRY glDepthRange (GLclampd zNear, GLclampd zFar);
WINGDIAPI void APIENTRY glDisable (GLenum cap);
WINGDIAPI void APIENTRY glDisableClientState (GLenum array);
WINGDIAPI void APIENTRY glDrawBuffer (GLenum mode);
WINGDIAPI void APIENTRY glDrawPixels (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
WINGDIAPI void APIENTRY glEdgeFlag (GLboolean flag);
WINGDIAPI void APIENTRY glEdgeFlagPointer (GLsizei stride, const GLvoid *pointer);
WINGDIAPI void APIENTRY glEdgeFlagv (const GLboolean *flag);
WINGDIAPI void APIENTRY glEnableClientState (GLenum array);
WINGDIAPI void APIENTRY glEnd (void);
WINGDIAPI void APIENTRY glEndList (void);
WINGDIAPI void APIENTRY glEvalCoord1d (GLdouble u);
WINGDIAPI void APIENTRY glEvalCoord1dv (const GLdouble *u);
WINGDIAPI void APIENTRY glEvalCoord1f (GLfloat u);
WINGDIAPI void APIENTRY glEvalCoord1fv (const GLfloat *u);
WINGDIAPI void APIENTRY glEvalCoord2d (GLdouble u, GLdouble v);
WINGDIAPI void APIENTRY glEvalCoord2dv (const GLdouble *u);
WINGDIAPI void APIENTRY glEvalCoord2f (GLfloat u, GLfloat v);
WINGDIAPI void APIENTRY glEvalCoord2fv (const GLfloat *u);
WINGDIAPI void APIENTRY glEvalMesh1 (GLenum mode, GLint i1, GLint i2);
WINGDIAPI void APIENTRY glEvalMesh2 (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
WINGDIAPI void APIENTRY glEvalPoint1 (GLint i);
WINGDIAPI void APIENTRY glEvalPoint2 (GLint i, GLint j);
WINGDIAPI void APIENTRY glFeedbackBuffer (GLsizei size, GLenum type, GLfloat *buffer);
WINGDIAPI void APIENTRY glFlush (void);
WINGDIAPI void APIENTRY glFogf (GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glFogfv (GLenum pname, const GLfloat *params);
WINGDIAPI void APIENTRY glFogi (GLenum pname, GLint param);
WINGDIAPI void APIENTRY glFogiv (GLenum pname, const GLint *params);
WINGDIAPI void APIENTRY glFrontFace (GLenum mode);
WINGDIAPI void APIENTRY glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
WINGDIAPI GLuint APIENTRY glGenLists (GLsizei range);
WINGDIAPI void APIENTRY glGetBooleanv (GLenum pname, GLboolean *params);
WINGDIAPI void APIENTRY glGetClipPlane (GLenum plane, GLdouble *equation);
WINGDIAPI void APIENTRY glGetDoublev (GLenum pname, GLdouble *params);
WINGDIAPI void APIENTRY glGetFloatv (GLenum pname, GLfloat *params);
WINGDIAPI void APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
WINGDIAPI void APIENTRY glGetLightiv (GLenum light, GLenum pname, GLint *params);
WINGDIAPI void APIENTRY glGetMapdv (GLenum target, GLenum query, GLdouble *v);
WINGDIAPI void APIENTRY glGetMapfv (GLenum target, GLenum query, GLfloat *v);
WINGDIAPI void APIENTRY glGetMapiv (GLenum target, GLenum query, GLint *v);
WINGDIAPI void APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
WINGDIAPI void APIENTRY glGetMaterialiv (GLenum face, GLenum pname, GLint *params);
WINGDIAPI void APIENTRY glGetPixelMapfv (GLenum map, GLfloat *values);
WINGDIAPI void APIENTRY glGetPixelMapuiv (GLenum map, GLuint *values);
WINGDIAPI void APIENTRY glGetPixelMapusv (GLenum map, GLushort *values);
WINGDIAPI void APIENTRY glGetPointerv (GLenum pname, GLvoid* *params);
WINGDIAPI void APIENTRY glGetPolygonStipple (GLubyte *mask);
WINGDIAPI void APIENTRY glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
WINGDIAPI void APIENTRY glGetTexEnviv (GLenum target, GLenum pname, GLint *params);
WINGDIAPI void APIENTRY glGetTexGendv (GLenum coord, GLenum pname, GLdouble *params);
WINGDIAPI void APIENTRY glGetTexGenfv (GLenum coord, GLenum pname, GLfloat *params);
WINGDIAPI void APIENTRY glGetTexGeniv (GLenum coord, GLenum pname, GLint *params);
WINGDIAPI void APIENTRY glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
WINGDIAPI void APIENTRY glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
WINGDIAPI void APIENTRY glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
WINGDIAPI void APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
WINGDIAPI void APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
WINGDIAPI void APIENTRY glHint (GLenum target, GLenum mode);
WINGDIAPI void APIENTRY glIndexMask (GLuint mask);
WINGDIAPI void APIENTRY glIndexPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
WINGDIAPI void APIENTRY glIndexd (GLdouble c);
WINGDIAPI void APIENTRY glIndexdv (const GLdouble *c);
WINGDIAPI void APIENTRY glIndexf (GLfloat c);
WINGDIAPI void APIENTRY glIndexfv (const GLfloat *c);
WINGDIAPI void APIENTRY glIndexi (GLint c);
WINGDIAPI void APIENTRY glIndexiv (const GLint *c);
WINGDIAPI void APIENTRY glIndexs (GLshort c);
WINGDIAPI void APIENTRY glIndexsv (const GLshort *c);
WINGDIAPI void APIENTRY glIndexub (GLubyte c);
WINGDIAPI void APIENTRY glIndexubv (const GLubyte *c);
WINGDIAPI void APIENTRY glInitNames (void);
WINGDIAPI void APIENTRY glInterleavedArrays (GLenum format, GLsizei stride, const GLvoid *pointer);
WINGDIAPI GLboolean APIENTRY glIsEnabled (GLenum cap);
WINGDIAPI GLboolean APIENTRY glIsList (GLuint list);
WINGDIAPI GLboolean APIENTRY glIsTexture (GLuint texture);
WINGDIAPI void APIENTRY glLightModelf (GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glLightModelfv (GLenum pname, const GLfloat *params);
WINGDIAPI void APIENTRY glLightModeli (GLenum pname, GLint param);
WINGDIAPI void APIENTRY glLightModeliv (GLenum pname, const GLint *params);
WINGDIAPI void APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glLightfv (GLenum light, GLenum pname, const GLfloat *params);
WINGDIAPI void APIENTRY glLighti (GLenum light, GLenum pname, GLint param);
WINGDIAPI void APIENTRY glLightiv (GLenum light, GLenum pname, const GLint *params);
WINGDIAPI void APIENTRY glLineStipple (GLint factor, GLushort pattern);
WINGDIAPI void APIENTRY glLineWidth (GLfloat width);
WINGDIAPI void APIENTRY glListBase (GLuint base);
WINGDIAPI void APIENTRY glLoadIdentity (void);
WINGDIAPI void APIENTRY glLoadMatrixd (const GLdouble *m);
WINGDIAPI void APIENTRY glLoadMatrixf (const GLfloat *m);
WINGDIAPI void APIENTRY glLoadName (GLuint name);
WINGDIAPI void APIENTRY glLogicOp (GLenum opcode);
WINGDIAPI void APIENTRY glMap1d (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
WINGDIAPI void APIENTRY glMap1f (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
WINGDIAPI void APIENTRY glMap2d (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
WINGDIAPI void APIENTRY glMap2f (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
WINGDIAPI void APIENTRY glMapGrid1d (GLint un, GLdouble u1, GLdouble u2);
WINGDIAPI void APIENTRY glMapGrid1f (GLint un, GLfloat u1, GLfloat u2);
WINGDIAPI void APIENTRY glMapGrid2d (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
WINGDIAPI void APIENTRY glMapGrid2f (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
WINGDIAPI void APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
WINGDIAPI void APIENTRY glMateriali (GLenum face, GLenum pname, GLint param);
WINGDIAPI void APIENTRY glMaterialiv (GLenum face, GLenum pname, const GLint *params);
WINGDIAPI void APIENTRY glMatrixMode (GLenum mode);
WINGDIAPI void APIENTRY glMultMatrixd (const GLdouble *m);
WINGDIAPI void APIENTRY glMultMatrixf (const GLfloat *m);
WINGDIAPI void APIENTRY glNewList (GLuint list, GLenum mode);
WINGDIAPI void APIENTRY glNormal3b (GLbyte nx, GLbyte ny, GLbyte nz);
WINGDIAPI void APIENTRY glNormal3bv (const GLbyte *v);
WINGDIAPI void APIENTRY glNormal3d (GLdouble nx, GLdouble ny, GLdouble nz);
WINGDIAPI void APIENTRY glNormal3dv (const GLdouble *v);
WINGDIAPI void APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
WINGDIAPI void APIENTRY glNormal3fv (const GLfloat *v);
WINGDIAPI void APIENTRY glNormal3i (GLint nx, GLint ny, GLint nz);
WINGDIAPI void APIENTRY glNormal3iv (const GLint *v);
WINGDIAPI void APIENTRY glNormal3s (GLshort nx, GLshort ny, GLshort nz);
WINGDIAPI void APIENTRY glNormal3sv (const GLshort *v);
WINGDIAPI void APIENTRY glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
WINGDIAPI void APIENTRY glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
WINGDIAPI void APIENTRY glPassThrough (GLfloat token);
WINGDIAPI void APIENTRY glPixelMapfv (GLenum map, GLsizei mapsize, const GLfloat *values);
WINGDIAPI void APIENTRY glPixelMapuiv (GLenum map, GLsizei mapsize, const GLuint *values);
WINGDIAPI void APIENTRY glPixelMapusv (GLenum map, GLsizei mapsize, const GLushort *values);
WINGDIAPI void APIENTRY glPixelStoref (GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glPixelTransferf (GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glPixelTransferi (GLenum pname, GLint param);
WINGDIAPI void APIENTRY glPixelZoom (GLfloat xfactor, GLfloat yfactor);
WINGDIAPI void APIENTRY glPointSize (GLfloat size);
WINGDIAPI void APIENTRY glPolygonMode (GLenum face, GLenum mode);
WINGDIAPI void APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
WINGDIAPI void APIENTRY glPolygonStipple (const GLubyte *mask);
WINGDIAPI void APIENTRY glPopAttrib (void);
WINGDIAPI void APIENTRY glPopClientAttrib (void);
WINGDIAPI void APIENTRY glPopMatrix (void);
WINGDIAPI void APIENTRY glPopName (void);
WINGDIAPI void APIENTRY glPrioritizeTextures (GLsizei n, const GLuint *textures, const GLclampf *priorities);
WINGDIAPI void APIENTRY glPushAttrib (GLbitfield mask);
WINGDIAPI void APIENTRY glPushClientAttrib (GLbitfield mask);
WINGDIAPI void APIENTRY glPushMatrix (void);
WINGDIAPI void APIENTRY glPushName (GLuint name);
WINGDIAPI void APIENTRY glRasterPos2d (GLdouble x, GLdouble y);
WINGDIAPI void APIENTRY glRasterPos2dv (const GLdouble *v);
WINGDIAPI void APIENTRY glRasterPos2f (GLfloat x, GLfloat y);
WINGDIAPI void APIENTRY glRasterPos2fv (const GLfloat *v);
WINGDIAPI void APIENTRY glRasterPos2i (GLint x, GLint y);
WINGDIAPI void APIENTRY glRasterPos2iv (const GLint *v);
WINGDIAPI void APIENTRY glRasterPos2s (GLshort x, GLshort y);
WINGDIAPI void APIENTRY glRasterPos2sv (const GLshort *v);
WINGDIAPI void APIENTRY glRasterPos3d (GLdouble x, GLdouble y, GLdouble z);
WINGDIAPI void APIENTRY glRasterPos3dv (const GLdouble *v);
WINGDIAPI void APIENTRY glRasterPos3f (GLfloat x, GLfloat y, GLfloat z);
WINGDIAPI void APIENTRY glRasterPos3fv (const GLfloat *v);
WINGDIAPI void APIENTRY glRasterPos3i (GLint x, GLint y, GLint z);
WINGDIAPI void APIENTRY glRasterPos3iv (const GLint *v);
WINGDIAPI void APIENTRY glRasterPos3s (GLshort x, GLshort y, GLshort z);
WINGDIAPI void APIENTRY glRasterPos3sv (const GLshort *v);
WINGDIAPI void APIENTRY glRasterPos4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
WINGDIAPI void APIENTRY glRasterPos4dv (const GLdouble *v);
WINGDIAPI void APIENTRY glRasterPos4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
WINGDIAPI void APIENTRY glRasterPos4fv (const GLfloat *v);
WINGDIAPI void APIENTRY glRasterPos4i (GLint x, GLint y, GLint z, GLint w);
WINGDIAPI void APIENTRY glRasterPos4iv (const GLint *v);
WINGDIAPI void APIENTRY glRasterPos4s (GLshort x, GLshort y, GLshort z, GLshort w);
WINGDIAPI void APIENTRY glRasterPos4sv (const GLshort *v);
WINGDIAPI void APIENTRY glReadBuffer (GLenum mode);
WINGDIAPI void APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
WINGDIAPI void APIENTRY glRectd (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
WINGDIAPI void APIENTRY glRectdv (const GLdouble *v1, const GLdouble *v2);
WINGDIAPI void APIENTRY glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
WINGDIAPI void APIENTRY glRectfv (const GLfloat *v1, const GLfloat *v2);
WINGDIAPI void APIENTRY glRecti (GLint x1, GLint y1, GLint x2, GLint y2);
WINGDIAPI void APIENTRY glRectiv (const GLint *v1, const GLint *v2);
WINGDIAPI void APIENTRY glRects (GLshort x1, GLshort y1, GLshort x2, GLshort y2);
WINGDIAPI void APIENTRY glRectsv (const GLshort *v1, const GLshort *v2);
WINGDIAPI GLint APIENTRY glRenderMode (GLenum mode);
WINGDIAPI void APIENTRY glRotated (GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
WINGDIAPI void APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
WINGDIAPI void APIENTRY glScaled (GLdouble x, GLdouble y, GLdouble z);
WINGDIAPI void APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
WINGDIAPI void APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
WINGDIAPI void APIENTRY glSelectBuffer (GLsizei size, GLuint *buffer);
WINGDIAPI void APIENTRY glShadeModel (GLenum mode);
WINGDIAPI void APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
WINGDIAPI void APIENTRY glStencilMask (GLuint mask);
WINGDIAPI void APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
WINGDIAPI void APIENTRY glTexCoord1d (GLdouble s);
WINGDIAPI void APIENTRY glTexCoord1dv (const GLdouble *v);
WINGDIAPI void APIENTRY glTexCoord1f (GLfloat s);
WINGDIAPI void APIENTRY glTexCoord1fv (const GLfloat *v);
WINGDIAPI void APIENTRY glTexCoord1i (GLint s);
WINGDIAPI void APIENTRY glTexCoord1iv (const GLint *v);
WINGDIAPI void APIENTRY glTexCoord1s (GLshort s);
WINGDIAPI void APIENTRY glTexCoord1sv (const GLshort *v);
WINGDIAPI void APIENTRY glTexCoord2d (GLdouble s, GLdouble t);
WINGDIAPI void APIENTRY glTexCoord2dv (const GLdouble *v);
WINGDIAPI void APIENTRY glTexCoord2f (GLfloat s, GLfloat t);
WINGDIAPI void APIENTRY glTexCoord2fv (const GLfloat *v);
WINGDIAPI void APIENTRY glTexCoord2i (GLint s, GLint t);
WINGDIAPI void APIENTRY glTexCoord2iv (const GLint *v);
WINGDIAPI void APIENTRY glTexCoord2s (GLshort s, GLshort t);
WINGDIAPI void APIENTRY glTexCoord2sv (const GLshort *v);
WINGDIAPI void APIENTRY glTexCoord3d (GLdouble s, GLdouble t, GLdouble r);
WINGDIAPI void APIENTRY glTexCoord3dv (const GLdouble *v);
WINGDIAPI void APIENTRY glTexCoord3f (GLfloat s, GLfloat t, GLfloat r);
WINGDIAPI void APIENTRY glTexCoord3fv (const GLfloat *v);
WINGDIAPI void APIENTRY glTexCoord3i (GLint s, GLint t, GLint r);
WINGDIAPI void APIENTRY glTexCoord3iv (const GLint *v);
WINGDIAPI void APIENTRY glTexCoord3s (GLshort s, GLshort t, GLshort r);
WINGDIAPI void APIENTRY glTexCoord3sv (const GLshort *v);
WINGDIAPI void APIENTRY glTexCoord4d (GLdouble s, GLdouble t, GLdouble r, GLdouble q);
WINGDIAPI void APIENTRY glTexCoord4dv (const GLdouble *v);
WINGDIAPI void APIENTRY glTexCoord4f (GLfloat s, GLfloat t, GLfloat r, GLfloat q);
WINGDIAPI void APIENTRY glTexCoord4fv (const GLfloat *v);
WINGDIAPI void APIENTRY glTexCoord4i (GLint s, GLint t, GLint r, GLint q);
WINGDIAPI void APIENTRY glTexCoord4iv (const GLint *v);
WINGDIAPI void APIENTRY glTexCoord4s (GLshort s, GLshort t, GLshort r, GLshort q);
WINGDIAPI void APIENTRY glTexCoord4sv (const GLshort *v);
WINGDIAPI void APIENTRY glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
WINGDIAPI void APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params);
WINGDIAPI void APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param);
WINGDIAPI void APIENTRY glTexEnviv (GLenum target, GLenum pname, const GLint *params);
WINGDIAPI void APIENTRY glTexGend (GLenum coord, GLenum pname, GLdouble param);
WINGDIAPI void APIENTRY glTexGendv (GLenum coord, GLenum pname, const GLdouble *params);
WINGDIAPI void APIENTRY glTexGenf (GLenum coord, GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glTexGenfv (GLenum coord, GLenum pname, const GLfloat *params);
WINGDIAPI void APIENTRY glTexGeni (GLenum coord, GLenum pname, GLint param);
WINGDIAPI void APIENTRY glTexGeniv (GLenum coord, GLenum pname, const GLint *params);
WINGDIAPI void APIENTRY glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
WINGDIAPI void APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
WINGDIAPI void APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
WINGDIAPI void APIENTRY glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
WINGDIAPI void APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
WINGDIAPI void APIENTRY glTranslated (GLdouble x, GLdouble y, GLdouble z);
WINGDIAPI void APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
WINGDIAPI void APIENTRY glVertex2d (GLdouble x, GLdouble y);
WINGDIAPI void APIENTRY glVertex2dv (const GLdouble *v);
WINGDIAPI void APIENTRY glVertex2f (GLfloat x, GLfloat y);
WINGDIAPI void APIENTRY glVertex2fv (const GLfloat *v);
WINGDIAPI void APIENTRY glVertex2i (GLint x, GLint y);
WINGDIAPI void APIENTRY glVertex2iv (const GLint *v);
WINGDIAPI void APIENTRY glVertex2s (GLshort x, GLshort y);
WINGDIAPI void APIENTRY glVertex2sv (const GLshort *v);
WINGDIAPI void APIENTRY glVertex3d (GLdouble x, GLdouble y, GLdouble z);
WINGDIAPI void APIENTRY glVertex3dv (const GLdouble *v);
WINGDIAPI void APIENTRY glVertex3f (GLfloat x, GLfloat y, GLfloat z);
WINGDIAPI void APIENTRY glVertex3fv (const GLfloat *v);
WINGDIAPI void APIENTRY glVertex3i (GLint x, GLint y, GLint z);
WINGDIAPI void APIENTRY glVertex3iv (const GLint *v);
WINGDIAPI void APIENTRY glVertex3s (GLshort x, GLshort y, GLshort z);
WINGDIAPI void APIENTRY glVertex3sv (const GLshort *v);
WINGDIAPI void APIENTRY glVertex4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
WINGDIAPI void APIENTRY glVertex4dv (const GLdouble *v);
WINGDIAPI void APIENTRY glVertex4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
WINGDIAPI void APIENTRY glVertex4fv (const GLfloat *v);
WINGDIAPI void APIENTRY glVertex4i (GLint x, GLint y, GLint z, GLint w);
WINGDIAPI void APIENTRY glVertex4iv (const GLint *v);
WINGDIAPI void APIENTRY glVertex4s (GLshort x, GLshort y, GLshort z, GLshort w);
WINGDIAPI void APIENTRY glVertex4sv (const GLshort *v);
WINGDIAPI void APIENTRY glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
#endif

typedef void (WINAPI *PFNGLBEGINPROC)(GLenum mode);
typedef void (WINAPI *PFNGLENDPROC)();
typedef void (WINAPI *PFNGLCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
typedef void (WINAPI *PFNGLCOLOR4UBPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
typedef void (WINAPI *PFNGLCOLOR4FPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (WINAPI *PFNGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (WINAPI *PFNGLTEXCOORD2FPROC)(GLfloat s, GLfloat t);
typedef void (WINAPI *PFNGLDISABLEPROC)(GLenum cap);
typedef void (WINAPI *PFNGLALPHAFUNCPROC)(GLenum func, GLclampf ref);
typedef void (WINAPI *PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (WINAPI *PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (WINAPI *PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);

#ifdef __GNUG__
#define GL_FN(a, b) a b;
#else
#define GL_FN(a, b) __declspec(selectany) a b;
#endif
#define GET_FN(a, b) a = (b)GetAnyGLFuncAddress(#a);

extern "C"
{
    
	///////////////////////////////////////////////////////////////////////////////////////////
	//					FUNCTION POINTERS
	///////////////////////////////////////////////////////////////////////////////////////////
    
	//
	//	Extensions
	//
    
    //WGL_ARB_extensions_string
	GL_FN(PFNWGLGETEXTENSIONSSTRINGARBPROC, wglGetExtensionsStringARB);
    
	//WGL_ARB_pixel_format
	GL_FN(PFNWGLGETPIXELFORMATATTRIBIVARBPROC, wglGetPixelFormatAttribivARB);	;
	GL_FN(PFNWGLGETPIXELFORMATATTRIBFVARBPROC, wglGetPixelFormatAttribfvARB);	;
	GL_FN(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB);
    
	//WGL_EXT_swap_control
	GL_FN(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT);
	GL_FN(PFNWGLGETSWAPINTERVALEXTPROC, wglGetSwapIntervalEXT);
    
	//WGL_ARB_pbuffer
	GL_FN(PFNWGLCREATEPBUFFERARBPROC, wglCreatePbufferARB);
	GL_FN(PFNWGLGETPBUFFERDCARBPROC, wglGetPbufferDCARB);
	GL_FN(PFNWGLRELEASEPBUFFERDCARBPROC, wglReleasePbufferDCARB);	;
	GL_FN(PFNWGLDESTROYPBUFFERARBPROC, wglDestroyPbufferARB);
	GL_FN(PFNWGLQUERYPBUFFERARBPROC, wglQueryPbufferARB);
    
	//WGL_ARB_render_texture
	GL_FN(PFNWGLBINDTEXIMAGEARBPROC, wglBindTexImageARB);
	GL_FN(PFNWGLRELEASETEXIMAGEARBPROC, wglReleaseTexImageARB);
	GL_FN(PFNWGLSETPBUFFERATTRIBARBPROC, wglSetPbufferAttribARB);	;
    
	//WGL_ARB_make_current_read
	GL_FN(PFNWGLMAKECONTEXTCURRENTARBPROC, wglMakeContextCurrentARB);	;
	GL_FN(PFNWGLGETCURRENTREADDCARBPROC, wglGetCurrentReadDCARB);	;
    
	//WGL_EXT_extensions_string
	GL_FN(PFNWGLGETEXTENSIONSSTRINGEXTPROC, wglGetExtensionsStringEXT);	;
    
	//WGL_ARB_buffer_region
	GL_FN(PFNWGLCREATEBUFFERREGIONARBPROC, wglCreateBufferRegionARB);	;
	GL_FN(PFNWGLDELETEBUFFERREGIONARBPROC, wglDeleteBufferRegionARB);	;
	GL_FN(PFNWGLSAVEBUFFERREGIONARBPROC, wglSaveBufferRegionARB);	;
	GL_FN(PFNWGLRESTOREBUFFERREGIONARBPROC, wglRestoreBufferRegionARB);	;
    
	//WGL_ATI_render_texture_rectangle NOTE: NOT FOUND IN MY wglExt.h FILE DOWNLOADED FROM OPENGL REFERENCE SITE!!!
    
	//WGL_I3D_genlock
	GL_FN(PFNWGLENABLEGENLOCKI3DPROC, wglEnableGenlockI3D);
	GL_FN(PFNWGLDISABLEGENLOCKI3DPROC, wglDisableGenlockI3D);
	GL_FN(PFNWGLISENABLEDGENLOCKI3DPROC, wglIsEnabledGenlockI3D);	;
	GL_FN(PFNWGLGENLOCKSOURCEI3DPROC, wglGenlockSourceI3D);
	GL_FN(PFNWGLGETGENLOCKSOURCEI3DPROC, wglGetGenlockSourceI3D);	;
	GL_FN(PFNWGLGENLOCKSOURCEEDGEI3DPROC, wglGenlockSourceEdgeI3D);
	GL_FN(PFNWGLGETGENLOCKSOURCEEDGEI3DPROC, wglGetGenlockSourceEdgeI3D);	;
	GL_FN(PFNWGLGENLOCKSAMPLERATEI3DPROC, wglGenlockSampleRateI3D);
	GL_FN(PFNWGLGETGENLOCKSAMPLERATEI3DPROC, wglGetGenlockSampleRateI3D);	;
	GL_FN(PFNWGLGENLOCKSOURCEDELAYI3DPROC, wglGenlockSourceDelayI3D);	;
	GL_FN(PFNWGLGETGENLOCKSOURCEDELAYI3DPROC, wglGetGenlockSourceDelayI3D);	;
	GL_FN(PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC, wglQueryGenlockMaxSourceDelayI3D);	;
    
	//WGL_NV_swap_group
	GL_FN(PFNWGLJOINSWAPGROUPNVPROC, wglJoinSwapGroupNV);
	GL_FN(PFNWGLBINDSWAPBARRIERNVPROC, wglBindSwapBarrierNV);
	GL_FN(PFNWGLQUERYSWAPGROUPNVPROC, wglQuerySwapGroupNV);
	GL_FN(PFNWGLQUERYMAXSWAPGROUPSNVPROC, wglQueryMaxSwapGroupsNV);
	GL_FN(PFNWGLQUERYFRAMECOUNTNVPROC, wglQueryFrameCountNV);
	GL_FN(PFNWGLRESETFRAMECOUNTNVPROC, wglResetFrameCountNV);
    
	//WGL_ARB_create_context
	GL_FN(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);	;
    
	//WGL_AMD_gpu_association
	GL_FN(PFNWGLGETGPUIDSAMDPROC, wglGetGPUIDsAMD);
	GL_FN(PFNWGLGETGPUINFOAMDPROC, wglGetGPUInfoAMD);
	GL_FN(PFNWGLGETCONTEXTGPUIDAMDPROC, wglGetContextGPUIDAMD);
	GL_FN(PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC, wglCreateAssociatedContextAMD);	;
	GL_FN(PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC, wglCreateAssociatedContextAttribsAMD);
	GL_FN(PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC, wglDeleteAssociatedContextAMD);	;
	GL_FN(PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC, wglMakeAssociatedContextCurrentAMD);
	GL_FN(PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC, wglGetCurrentAssociatedContextAMD);
	GL_FN(PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC, wglBlitContextFramebufferAMD);	;
    
	//WGL_AMDX_gpu_association NOTE: ANOTHER ONE WITH NOTHING IN wglExt.h FILE!
    
	//WGL_NV_DX_interop
	GL_FN(PFNWGLDXSETRESOURCESHAREHANDLENVPROC, wglDXSetResourceShareHandleNV);	;
	GL_FN(PFNWGLDXOPENDEVICENVPROC, wglDXOpenDeviceNV);
	GL_FN(PFNWGLDXCLOSEDEVICENVPROC, wglDXCloseDeviceNV);
	GL_FN(PFNWGLDXREGISTEROBJECTNVPROC, wglDXRegisterObjectNV);
	GL_FN(PFNWGLDXUNREGISTEROBJECTNVPROC, wglDXUnregisterObjectNV);
	GL_FN(PFNWGLDXOBJECTACCESSNVPROC, wglDXObjectAccessNV);
	GL_FN(PFNWGLDXLOCKOBJECTSNVPROC, wglDXLockObjectsNV);
	GL_FN(PFNWGLDXUNLOCKOBJECTSNVPROC, wglDXUnlockObjectsNV);
    
    
    
	//
	//	GL Functions
	//
    
	// Debug/Init Functions
	GL_FN(PFNGLGETERRORPROC, glGetError);
	GL_FN(PFNGLGETINTEGERVPROC, glGetIntegerv);
	GL_FN(PFNGLGETSTRINGIPROC, glGetStringi);
	GL_FN(PFNGLGETSTRINGPROC, glGetString);
    
	GL_FN(PFNGLGETSHADERIVPROC, glGetShaderiv);
	GL_FN(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
	GL_FN(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
	GL_FN(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
    
	GL_FN(PFNGLENABLEPROC, glEnable);
	GL_FN(PFNGLFINISHPROC, glFinish);
    
    GL_FN(PFNGLBEGINPROC, glBegin);
    GL_FN(PFNGLENDPROC, glEnd);
    
    GL_FN(PFNGLCOLOR3UBPROC, glColor3ub);
    GL_FN(PFNGLCOLOR4UBPROC, glColor4ub);
    GL_FN(PFNGLCOLOR4FPROC, glColor4f);
    
    GL_FN(PFNGLVERTEX3FPROC, glVertex3f);
    GL_FN(PFNGLTEXCOORD2FPROC, glTexCoord2f);
    
    GL_FN(PFNGLDISABLEPROC, glDisable);
    GL_FN(PFNGLALPHAFUNCPROC, glAlphaFunc);
    GL_FN(PFNGLBLENDFUNCPROC, glBlendFunc);
    GL_FN(PFNGLTEXPARAMETERIVPROC, glTexParameteriv);
    
    // Blitting Functions
    GL_FN(PFNGLVIEWPORTPROC, glViewport);
	GL_FN(PFNGLCLEARCOLORPROC, glClearColor);
	GL_FN(PFNGLCLEARPROC, glClear);
    GL_FN(PFNGLCLEARDEPTHPROC, glClearDepth);
    GL_FN(PFNGLDEPTHFUNCPROC, glDepthFunc);
	GL_FN(PFNGLDRAWARRAYSPROC, glDrawArrays);
	GL_FN(PFNGLDRAWELEMENTSPROC, glDrawElements);
    
	// GPU Memory Managment
	GL_FN(PFNGLGENBUFFERSPROC, glGenBuffers);
    GL_FN(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
	GL_FN(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
    GL_FN(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
	GL_FN(PFNGLBINDBUFFERPROC, glBindBuffer);
	GL_FN(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
	GL_FN(PFNGLBUFFERDATAPROC, glBufferData);
    GL_FN(PFNGLPIXELSTOREIPROC, glPixelStorei);
    
	// Shader Functions
	GL_FN(PFNGLCREATESHADERPROC, glCreateShader);
	GL_FN(PFNGLCREATEPROGRAMPROC, glCreateProgram);
	GL_FN(PFNGLDELETESHADERPROC, glDeleteShader);
    
	GL_FN(PFNGLSHADERSOURCEPROC, glShaderSource);
	GL_FN(PFNGLCOMPILESHADERPROC, glCompileShader);
	GL_FN(PFNGLATTACHSHADERPROC, glAttachShader);
    GL_FN(PFNGLBINDFRAGDATALOCATIONPROC, glBindFragDataLocation);
	GL_FN(PFNGLLINKPROGRAMPROC, glLinkProgram);
	GL_FN(PFNGLUSEPROGRAMPROC, glUseProgram);
    
	GL_FN(PFNGLGETUNIFORMFVPROC, glGetUniformfv);
	GL_FN(PFNGLGETUNIFORMIVPROC, glGetUniformiv);
	GL_FN(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv);
	GL_FN(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
	GL_FN(PFNGLUNIFORM4FPROC, glUniform4f);
	GL_FN(PFNGLUNIFORM3FPROC, glUniform3f);
	GL_FN(PFNGLUNIFORM2FPROC, glUniform2f);
	GL_FN(PFNGLUNIFORM1FPROC, glUniform1f);
    
	GL_FN(PFNGLUNIFORM4FVPROC, glUniform4fv);
	GL_FN(PFNGLUNIFORM3FVPROC, glUniform3fv);
	GL_FN(PFNGLUNIFORM2FVPROC, glUniform2fv);
	GL_FN(PFNGLUNIFORM1FVPROC, glUniform1fv);
    
	GL_FN(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
	GL_FN(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
	GL_FN(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
    
	GL_FN(PFNGLUNIFORM4DPROC, glUniform4d);
	GL_FN(PFNGLUNIFORM3DPROC, glUniform3d);
	GL_FN(PFNGLUNIFORM2DPROC, glUniform2d);
	GL_FN(PFNGLUNIFORM1DPROC, glUniform1d);
    
	GL_FN(PFNGLUNIFORM4IPROC, glUniform4i);
	GL_FN(PFNGLUNIFORM3IPROC, glUniform3i);
	GL_FN(PFNGLUNIFORM2IPROC, glUniform2i);
	GL_FN(PFNGLUNIFORM1IPROC, glUniform1i);
    
    GL_FN(PFNGLUNIFORM4UIPROC, glUniform4ui);
	GL_FN(PFNGLUNIFORM3UIPROC, glUniform3ui);
	GL_FN(PFNGLUNIFORM2UIPROC, glUniform2ui);
	GL_FN(PFNGLUNIFORM1UIPROC, glUniform1ui);
    
	GL_FN(PFNGLTEXPARAMETERIPROC, glTexParameteri);
	GL_FN(PFNGLTEXPARAMETERFVPROC, glTexParameterfv);
    
	GL_FN(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
	GL_FN(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    GL_FN(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv);
    
	// Texture Functions
    
	GL_FN(PFNGLGENTEXTURESPROC, glGenTextures);
	GL_FN(PFNGLBINDTEXTUREPROC, glBindTexture);
    GL_FN(PFNGLOBJECTLABELPROC, glObjectLabel);
	GL_FN(PFNGLTEXIMAGE2DPROC, glTexImage2D);
	GL_FN(PFNGLACTIVETEXTUREPROC, glActiveTexture);
    GL_FN(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
    
	GL_FN(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
    
    
    extern const GLubyte* APIENTRY ls_glUErrorString( GLenum errorCode );
    GLint ls_glVersion();
    
#ifdef LS_PLAT_WINDOWS
    void ls_glLoadFunc(HDC DeviceContext);
#endif
}

#endif //LS_OPENGL_H

#ifdef LS_OPENGL_IMPLEMENTATION

///////////////////////////////////////////////////////////////////////////////////////////
//					LOADING FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////

static void *GetAnyGLFuncAddress(const char *name)
{
    void *p = (void *)wglGetProcAddress(name);
    if ((p == 0) || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
    {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p = (void *)GetProcAddress(module, name);
    }
    
    return p;
}

GLint ls_glVersion()
{
    GLint Result = 0;
    GLint Major = 0;
    GLint Minor = 0;
    
    glGetIntegerv(GL_MAJOR_VERSION, &Major);
    if (Major == 0)
    {
        GLenum Error = glGetError();
        ls_printf("In getGLVersion error: %d\n", Error);
    }
    
    glGetIntegerv(GL_MINOR_VERSION, &Minor);
    if (Minor == 0)
    {
        GLenum Error = glGetError();
        ls_printf("In getGLVersion error: %d\n", Error);
    }
    
    Result = (Major * 10) + Minor;
    return Result;
}
#ifdef LS_PLAT_WINDOWS
void ls_glLoadFunc(HDC DeviceContext)
{
    glGetIntegerv  = (PFNGLGETINTEGERVPROC)GetAnyGLFuncAddress("glGetIntegerv");
    glGetStringi   = (PFNGLGETSTRINGIPROC)GetAnyGLFuncAddress("glGetStringi");
    glGetString	= (PFNGLGETSTRINGPROC)GetAnyGLFuncAddress("glGetString");
    glGetError	 = (PFNGLGETERRORPROC)GetAnyGLFuncAddress("glGetError");
    
    GLint Version = ls_glVersion();
    
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)GetAnyGLFuncAddress("wglGetExtensionsStringARB");
    const char *extensions = wglGetExtensionsStringARB(DeviceContext);
    
    
    //GET_FN(wglCreateContextAttribsARB, PFNWGLCREATECONTEXTATTRIBSARBPROC);
    //GET_FN(wglChoosePixelFormatARB, PFNWGLCHOOSEPIXELFORMATARBPROC);
    
    GET_FN(glBegin, PFNGLBEGINPROC);
    GET_FN(glEnd, PFNGLENDPROC);
    GET_FN(glColor3ub, PFNGLCOLOR3UBPROC);
    GET_FN(glColor4ub, PFNGLCOLOR4UBPROC);
    GET_FN(glColor4f, PFNGLCOLOR4FPROC);
    GET_FN(glVertex3f, PFNGLVERTEX3FPROC);
    GET_FN(glTexCoord2f, PFNGLTEXCOORD2FPROC);
    GET_FN(glDisable, PFNGLDISABLEPROC);
    GET_FN(glAlphaFunc, PFNGLALPHAFUNCPROC);
    GET_FN(glBlendFunc, PFNGLBLENDFUNCPROC);
    GET_FN(glTexParameteriv, PFNGLTEXPARAMETERIVPROC);
    
    //@TODO: This is actually not enough to check if we have these extensions, gonna have to implement more extensive checks later.
    
#ifdef WGL_ARB_pixel_format
    GET_FN(wglGetPixelFormatAttribivARB, PFNWGLGETPIXELFORMATATTRIBIVARBPROC);
    GET_FN(wglGetPixelFormatAttribfvARB, PFNWGLGETPIXELFORMATATTRIBFVARBPROC);
#endif
    
    
#ifdef WGL_EXT_swap_control
    GET_FN(wglSwapIntervalEXT, PFNWGLSWAPINTERVALEXTPROC);
    GET_FN(wglGetSwapIntervalEXT, PFNWGLGETSWAPINTERVALEXTPROC);
#endif
    
    
#ifdef WGL_ARB_pbuffer
    GET_FN(wglCreatePbufferARB, PFNWGLCREATEPBUFFERARBPROC);
    GET_FN(wglGetPbufferDCARB, PFNWGLGETPBUFFERDCARBPROC);
    GET_FN(wglReleasePbufferDCARB, PFNWGLRELEASEPBUFFERDCARBPROC);
    GET_FN(wglDestroyPbufferARB, PFNWGLDESTROYPBUFFERARBPROC);
    GET_FN(wglQueryPbufferARB, PFNWGLQUERYPBUFFERARBPROC);
#endif
    
    
#ifdef WGL_ARB_render_texture
    GET_FN(wglBindTexImageARB, PFNWGLBINDTEXIMAGEARBPROC);
    GET_FN(wglReleaseTexImageARB, PFNWGLRELEASETEXIMAGEARBPROC);
    GET_FN(wglSetPbufferAttribARB, PFNWGLSETPBUFFERATTRIBARBPROC);
#endif
    
    
#ifdef WGL_ARB_make_current_read
    GET_FN(wglMakeContextCurrentARB, PFNWGLMAKECONTEXTCURRENTARBPROC);
    GET_FN(wglGetCurrentReadDCARB, PFNWGLGETCURRENTREADDCARBPROC);
#endif
    
    
#ifdef WGL_EXT_extensions_string
    GET_FN(wglGetExtensionsStringEXT, PFNWGLGETEXTENSIONSSTRINGEXTPROC);
#endif
    
    
#ifdef WGL_ARB_buffer_region
    GET_FN(wglCreateBufferRegionARB, PFNWGLCREATEBUFFERREGIONARBPROC);
    GET_FN(wglDeleteBufferRegionARB, PFNWGLDELETEBUFFERREGIONARBPROC);
    GET_FN(wglSaveBufferRegionARB, PFNWGLSAVEBUFFERREGIONARBPROC);
    GET_FN(wglRestoreBufferRegionARB, PFNWGLRESTOREBUFFERREGIONARBPROC);
#endif
    
    
#ifdef WGL_I3D_genlock
    GET_FN(wglEnableGenlockI3D, PFNWGLENABLEGENLOCKI3DPROC);
    GET_FN(wglDisableGenlockI3D, PFNWGLDISABLEGENLOCKI3DPROC);
    GET_FN(wglIsEnabledGenlockI3D, PFNWGLISENABLEDGENLOCKI3DPROC);
    GET_FN(wglGenlockSourceI3D, PFNWGLGENLOCKSOURCEI3DPROC);
    GET_FN(wglGetGenlockSourceI3D, PFNWGLGETGENLOCKSOURCEI3DPROC);
    GET_FN(wglGenlockSourceEdgeI3D, PFNWGLGENLOCKSOURCEEDGEI3DPROC);
    GET_FN(wglGetGenlockSourceEdgeI3D, PFNWGLGETGENLOCKSOURCEEDGEI3DPROC);
    GET_FN(wglGenlockSampleRateI3D, PFNWGLGENLOCKSAMPLERATEI3DPROC);
    GET_FN(wglGetGenlockSampleRateI3D, PFNWGLGETGENLOCKSAMPLERATEI3DPROC);
    GET_FN(wglGenlockSourceDelayI3D, PFNWGLGENLOCKSOURCEDELAYI3DPROC);
    GET_FN(wglGetGenlockSourceDelayI3D, PFNWGLGETGENLOCKSOURCEDELAYI3DPROC);
    GET_FN(wglQueryGenlockMaxSourceDelayI3D, PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC);
#endif
    
    
#ifdef WGL_NV_swap_group
    GET_FN(wglJoinSwapGroupNV, PFNWGLJOINSWAPGROUPNVPROC);
    GET_FN(wglBindSwapBarrierNV, PFNWGLBINDSWAPBARRIERNVPROC);
    GET_FN(wglQuerySwapGroupNV, PFNWGLQUERYSWAPGROUPNVPROC);
    GET_FN(wglQueryMaxSwapGroupsNV, PFNWGLQUERYMAXSWAPGROUPSNVPROC);
    GET_FN(wglQueryFrameCountNV, PFNWGLQUERYFRAMECOUNTNVPROC);
    GET_FN(wglResetFrameCountNV, PFNWGLRESETFRAMECOUNTNVPROC);
#endif
    
#ifdef WGL_AMD_gpu_association
    GET_FN(wglGetGPUIDsAMD, PFNWGLGETGPUIDSAMDPROC);
    GET_FN(wglGetGPUInfoAMD, PFNWGLGETGPUINFOAMDPROC);
    GET_FN(wglGetContextGPUIDAMD, PFNWGLGETCONTEXTGPUIDAMDPROC);
    GET_FN(wglCreateAssociatedContextAMD, PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC);
    GET_FN(wglCreateAssociatedContextAttribsAMD, PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC);
    GET_FN(wglDeleteAssociatedContextAMD, PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC);
    GET_FN(wglMakeAssociatedContextCurrentAMD, PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC);
    GET_FN(wglGetCurrentAssociatedContextAMD, PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC);
    GET_FN(wglBlitContextFramebufferAMD, PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC);
#endif
    
#ifdef WGL_NV_DX_interop
    GET_FN(wglDXSetResourceShareHandleNV, PFNWGLDXSETRESOURCESHAREHANDLENVPROC);
    GET_FN(wglDXOpenDeviceNV, PFNWGLDXOPENDEVICENVPROC);
    GET_FN(wglDXCloseDeviceNV, PFNWGLDXCLOSEDEVICENVPROC);
    GET_FN(wglDXRegisterObjectNV, PFNWGLDXREGISTEROBJECTNVPROC);
    GET_FN(wglDXUnregisterObjectNV, PFNWGLDXUNREGISTEROBJECTNVPROC);
    GET_FN(wglDXObjectAccessNV, PFNWGLDXOBJECTACCESSNVPROC);
    GET_FN(wglDXLockObjectsNV, PFNWGLDXLOCKOBJECTSNVPROC);
    GET_FN(wglDXUnlockObjectsNV, PFNWGLDXUNLOCKOBJECTSNVPROC);
#endif
    
    
    if (Version >= 33)
    {
        GET_FN(glGetShaderiv, PFNGLGETSHADERIVPROC);
        GET_FN(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
        GET_FN(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
        GET_FN(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC);
        
        GET_FN(glEnable, PFNGLENABLEPROC);
        GET_FN(glFinish, PFNGLFINISHPROC);
        
        GET_FN(glViewport, PFNGLVIEWPORTPROC);
        GET_FN(glClearColor, PFNGLCLEARCOLORPROC);
        GET_FN(glClear, PFNGLCLEARPROC);
        GET_FN(glClearDepth, PFNGLCLEARDEPTHPROC);
        GET_FN(glDepthFunc, PFNGLDEPTHFUNCPROC);
        GET_FN(glDrawArrays, PFNGLDRAWARRAYSPROC);
        GET_FN(glDrawElements, PFNGLDRAWELEMENTSPROC);
        
        GET_FN(glGenBuffers, PFNGLGENBUFFERSPROC);
        GET_FN(glDeleteBuffers, PFNGLDELETEBUFFERSPROC);
        GET_FN(glGenVertexArrays,PFNGLGENVERTEXARRAYSPROC);
        GET_FN(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC);
        GET_FN(glBindBuffer, PFNGLBINDBUFFERPROC);
        GET_FN(glBindVertexArray,PFNGLBINDVERTEXARRAYPROC);
        GET_FN(glBufferData, PFNGLBUFFERDATAPROC);
        GET_FN(glPixelStorei, PFNGLPIXELSTOREIPROC);
        
        GET_FN(glCreateShader, PFNGLCREATESHADERPROC);
        GET_FN(glCreateProgram, PFNGLCREATEPROGRAMPROC);
        GET_FN(glDeleteShader, PFNGLDELETESHADERPROC);
        
        GET_FN(glShaderSource, PFNGLSHADERSOURCEPROC);
        GET_FN(glCompileShader, PFNGLCOMPILESHADERPROC);
        GET_FN(glAttachShader, PFNGLATTACHSHADERPROC);
        GET_FN(glBindFragDataLocation, PFNGLBINDFRAGDATALOCATIONPROC);
        GET_FN(glLinkProgram, PFNGLLINKPROGRAMPROC);
        GET_FN(glUseProgram, PFNGLUSEPROGRAMPROC);
        
        GET_FN(glGetUniformfv, PFNGLGETUNIFORMFVPROC);
        GET_FN(glGetUniformiv, PFNGLGETUNIFORMIVPROC);
        GET_FN(glGetUniformuiv, PFNGLGETUNIFORMUIVPROC);
        GET_FN(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);
        GET_FN(glUniform4f, PFNGLUNIFORM4FPROC);
        GET_FN(glUniform3f, PFNGLUNIFORM3FPROC);
        GET_FN(glUniform2f, PFNGLUNIFORM2FPROC);
        GET_FN(glUniform1f, PFNGLUNIFORM1FPROC);
        
        GET_FN(glUniform4fv, PFNGLUNIFORM4FVPROC);
        GET_FN(glUniform3fv, PFNGLUNIFORM3FVPROC);
        GET_FN(glUniform2fv, PFNGLUNIFORM2FVPROC);
        GET_FN(glUniform1fv, PFNGLUNIFORM1FVPROC);
        
        GET_FN(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);
        GET_FN(glUniformMatrix3fv, PFNGLUNIFORMMATRIX3FVPROC);
        GET_FN(glUniformMatrix2fv, PFNGLUNIFORMMATRIX2FVPROC);
        
        GET_FN(glUniform4d, PFNGLUNIFORM4DPROC);
        GET_FN(glUniform3d, PFNGLUNIFORM3DPROC);
        GET_FN(glUniform2d, PFNGLUNIFORM2DPROC);
        GET_FN(glUniform1d, PFNGLUNIFORM1DPROC);
        
        GET_FN(glUniform4i, PFNGLUNIFORM4IPROC);
        GET_FN(glUniform3i, PFNGLUNIFORM3IPROC);
        GET_FN(glUniform2i, PFNGLUNIFORM2IPROC);
        GET_FN(glUniform1i, PFNGLUNIFORM1IPROC);
        
        GET_FN(glUniform4ui, PFNGLUNIFORM4UIPROC);
        GET_FN(glUniform3ui, PFNGLUNIFORM3UIPROC);
        GET_FN(glUniform2ui, PFNGLUNIFORM2UIPROC);
        GET_FN(glUniform1ui, PFNGLUNIFORM1UIPROC);
        
        GET_FN(glTexParameteri, PFNGLTEXPARAMETERIPROC);
        GET_FN(glTexParameterfv, PFNGLTEXPARAMETERFVPROC);
        
        GET_FN(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
        GET_FN(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC);
        GET_FN(glGetVertexAttribIuiv, PFNGLGETVERTEXATTRIBIUIVPROC);
        
        GET_FN(glGenTextures, PFNGLGENTEXTURESPROC);
        GET_FN(glBindTexture, PFNGLBINDTEXTUREPROC);
        GET_FN(glObjectLabel, PFNGLOBJECTLABELPROC);
        GET_FN(glTexImage2D, PFNGLTEXIMAGE2DPROC);
        GET_FN(glActiveTexture, PFNGLACTIVETEXTUREPROC);
        
        GET_FN(glGetAttribLocation, PFNGLGETATTRIBLOCATIONPROC);
        
        GET_FN(glGenerateMipmap, PFNGLGENERATEMIPMAPPROC);
    }
}


#endif //LS_PLAT_WINDOWS

#undef GL_FN
#undef GET_FN

#endif //LS_OPENGL_IMPLEMENTATION