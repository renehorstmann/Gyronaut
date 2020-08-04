#define DEBUG
#include "utilc/alloc.h"
#include "r/r.h"
#include "r/batch_rects.h"
#include "cglm/cglm.h"

// x, y, u, v
static const float buffer[] = {
	-1, -1, 0, 1,
	+1, -1, 1, 1,
	-1, +1, 0, 0,
	-1, +1, 0, 0,
	+1, -1, 1, 1,
	+1, +1, 1, 0
};

void r_batch_rects_init(rBatchRects *self, int num, const char *tex_file, const float *vp) {
	self->instances = New(struct rBatchRectsInstance_s, num);
	self->num = num;
	self->vp = vp;
	
	
	for(int i=0; i<num; i++)
	    glm_mat4_identity(self->instances[i].m);
	
	self->program = r_compile_glsl_from_files((char *[]){
		"res/shader/r/batch_rects.vsh",
		"res/shader/r/batch_rects.fsh",
		NULL});

	self->tex = r_load_texture_from_file(tex_file);

	glGenVertexArrays(1, &self->vao);
	glBindVertexArray(self->vao);

	glGenBuffers(1, &self->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
	glBufferData(GL_ARRAY_BUFFER,
				 sizeof(buffer),
				 buffer,
				 GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
						  4 * sizeof(float), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
						  4 * sizeof(float),
						  (void *)(2 * sizeof(float)));
						 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// instanced
	glGenBuffers(1, &self->instance_bo);
	glBindBuffer(GL_ARRAY_BUFFER, self->instance_bo);
	glBufferData(GL_ARRAY_BUFFER,
				 num * sizeof(struct rBatchRectsInstance_s),
				 self->instances,
				 GL_STREAM_DRAW);
				 
	glBindVertexArray(self->vao);
	
	glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16, 0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16, 4);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16, 8);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16, 12);
    
    //glVertexAttribDivisor(2, 1);  
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glUniform1i(glGetUniformLocation(self->program, tex_file), self->tex);

	// unbind
	glBindVertexArray(0);
}

void r_batch_rects_kill(rBatchRects *self) {
	free(self->instances);
	glDeleteProgram(self->program);
	glDeleteVertexArrays(1, &self->vao);
	glDeleteBuffers(1, &self->vbo);
	glDeleteBuffers(1, &self->instance_bo);
	glDeleteTextures(1, &self->tex);
	*self = (rBatchRects) {0};
}

void r_batch_rects_update(rBatchRects *self) {
    //glm_mat4_print(self->instances[0].m, stdout);
    glBindBuffer(GL_ARRAY_BUFFER, self->instance_bo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 
        self->num * sizeof(struct rBatchRectsInstance_s), self->instances);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void r_batch_rects_render(rBatchRects *self) {
	glUseProgram(self->program);
	
	glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
					   1, GL_FALSE, self->vp);

	glActiveTexture(self->tex);
	glBindTexture(GL_TEXTURE_2D, self->tex);

	glBindVertexArray(self->vao);
	//glDrawArraysInstanced(GL_TRIANGLES, 0, 6, self->num);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	
	glUseProgram(0);
}
