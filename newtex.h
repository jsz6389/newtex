/* SPDX-License-Identifier: GPL-2.0-only
 *
 * newtex.h
 *
 * A utility for creating new files from templates
 *
 * Copyright (C) 2021 Jakob Zielinski <jakobzee3@gmail.com>
 */
#ifndef _NEWTEX_H_
#define _NEWTEX_H_


/*
 * Stores flag value bytes
 *
 * FLAG_WRITE:      Open the file after it is created
 * FLAG_VERBOSE:    Verbose output
 */
enum flag_e {
    FLAG_WRITE = 0b000000001,
    FLAG_VERBOSE = 0b00000010
};

#endif
