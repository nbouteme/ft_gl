#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 11:08:14 by nbouteme          #+#    #+#              #
#    Updated: 2016/04/01 14:07:39 by nbouteme         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf
OPTS =	-O3 -march=native -mtune=native -ffinite-math-only -ftree-vectorize\
	-funsafe-math-optimizations -fno-math-errno -ffast-math -mavx -mmmx -mfpmath=sse\

#OPTS = -g -mavx -mmmx

UNAME := $(shell uname)
#$(shell make -s -C minilibx)
ifeq ($(UNAME), Linux)
SUPF += -lm -Lminilibx -lmlx -lX11 -lXext
else
SUPL += -lm -lmlx -framework OpenGL -framework AppKit
endif

#OPTS = -g

##################
include mkgen.mk #
##################
