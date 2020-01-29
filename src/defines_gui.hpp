#pragma once


const bool full_screen_mode = false;

const unsigned int window_x = 10;
const unsigned int window_y = 20;
const unsigned int window_width = 1420;
const unsigned int window_height = 820;

const unsigned sizeof_pixel = 4;
const unsigned pdp_win_width = pdp_screen_width * sizeof_pixel;
const unsigned pdp_win_height = pdp_screen_height * sizeof_pixel;
const unsigned pdp_win_x = 150;
const unsigned pdp_win_y = 10;

static_assert(window_width - pdp_win_width > 100);
static_assert(window_height - pdp_win_height > 150);

const unsigned button_width = 100;
const unsigned button_height = 40;

const unsigned pdp_y_border = pdp_win_y + pdp_win_height;
const unsigned button_w_dist = (window_width - 2 * button_width) / 3;
const unsigned button_h_dist = (window_height - (pdp_y_border + button_height)) / 2;



const unsigned button_offset_x = button_width + 30;
const unsigned button_offset_y = button_height + 30;

const unsigned button_x0 = 30;
const unsigned button_y0 = 545;


//-------------------------------------------------------------------
//buttons
//-------------------------------------------------------------------
const unsigned step_x = button_x0 + 0 * button_offset_x;
const unsigned step_y = button_y0 + 0 * button_offset_y;

const unsigned breakpoint_x = button_x0 + 0 * button_offset_x;
const unsigned breakpoint_y = button_y0 + 1 * button_offset_y;

const unsigned stop_x = button_x0 + 0 * button_offset_x;
const unsigned stop_y = button_y0 + 2 * button_offset_y;


const unsigned run_x = button_x0 + 1 * button_offset_x;
const unsigned run_y = button_y0 + 0 * button_offset_y;

const unsigned reset_x = button_x0 + 1 * button_offset_x;
const unsigned reset_y = button_y0 + 1 * button_offset_y;

const unsigned exit_x = button_x0 + 1 * button_offset_x;
const unsigned exit_y = button_y0 + 2 * button_offset_y;


const unsigned input_x = button_x0 + 2 * button_offset_x;
const unsigned input_y = button_y0 + 0 * button_offset_y;


const unsigned load_exe_x = button_x0 + 3 * button_offset_x;
const unsigned load_exe_y = button_y0 + 0 * button_offset_y;

const unsigned load_mem_x = button_x0 + 3 * button_offset_x;
const unsigned load_mem_y = button_y0 + 1 * button_offset_y;

const unsigned load_regs_flags_x = button_x0 + 3 * button_offset_x;
const unsigned load_regs_flags_y = button_y0 + 2 * button_offset_y;
//-------------------------------------------------------------------
//CheckBoxes
//-------------------------------------------------------------------
const unsigned checkbox_x0 = 30;
const unsigned checkbox_y0 = 740;

const unsigned checkbox_offset_x = 200;
//const unsigned checkbox_offset_y0 = 40;

const unsigned checkbox_width = button_width+30;
const unsigned checkbox_height = button_height;

const unsigned synchronization_x = checkbox_x0 + 0 * checkbox_offset_x;
const unsigned synchronization_y = checkbox_y0;

const unsigned cache_x = checkbox_x0 + 1 * checkbox_offset_x;
const unsigned cache_y = checkbox_y0;

const unsigned pipeline_x = checkbox_x0 + 2 * checkbox_offset_x;
const unsigned pipeline_y = checkbox_y0;
//-------------------------------------------------------------------
//regs and flags
//-------------------------------------------------------------------
const int r_regs_amount = 8;
const int flags_amount = 6;

const int reg_x0 = 30;
const int reg_y0 = 20;

const int reg_descr_width = 20;
const int reg_descr_height = 20;
const int reg_width = 60;
const int reg_height = 20;

const int reg_offset_y = reg_descr_width + 5;
const int reg_descr_offset_x = reg_descr_height + 5;

const int regs_ys[r_regs_amount] =
{
	reg_y0 + 1 * reg_offset_y,
	reg_y0 + 2 * reg_offset_y,
	reg_y0 + 3 * reg_offset_y,
	reg_y0 + 4 * reg_offset_y,
	reg_y0 + 5 * reg_offset_y,
	reg_y0 + 6 * reg_offset_y,
	reg_y0 + 7 * reg_offset_y,
	reg_y0 + 8 * reg_offset_y,
};

const int flags_ys[flags_amount] =
{
	reg_y0 + 9 * reg_offset_y,
	reg_y0 + 10 * reg_offset_y,
	reg_y0 + 11 * reg_offset_y,
	reg_y0 + 12 * reg_offset_y,
	reg_y0 + 13 * reg_offset_y,
	reg_y0 + 14 * reg_offset_y,
};


const int bp_x = reg_x0;
const int bp_y = reg_y0;





const unsigned RegX = 30;
const unsigned RegY = 45;
const unsigned RegFGap = 5;
//-------------------------------------------------------------------
//ListBoxes
//-------------------------------------------------------------------
const unsigned desc_box_width = 300;
const unsigned desc_box_height = 20;

const unsigned list_box_width = desc_box_width;
const unsigned list_box_height = 350;


const unsigned ram_x = 700;
const unsigned ram_y = 10;

const unsigned vram_x = ram_x;
const unsigned vram_y = 400;

const unsigned rom_x = 1050;
const unsigned rom_y = ram_y;

const unsigned io_x = rom_x;
const unsigned io_y = vram_y;


const unsigned list_descr_offset = 5;


//-------------------------------------------------------------------
//Command numbs
//-------------------------------------------------------------------
//
//buttons: from 1 to 30
//
const UINT MSG_DRAW = 0x8000;
const WPARAM RUN_BUTTON = 1;
const WPARAM EXIT_BUTTON = 2;
const WPARAM INPUT_BUTTON = 3;
const WPARAM LOAD_EXE_BUTTON = 4;
const WPARAM LOAD_MEM_BUTTON = 5;
const WPARAM LOAD_REGS_BUTTON = 6;
const WPARAM STOP_BUTTON = 7;
const WPARAM RESET_BUTTON = 8;
const WPARAM BREAKPOINT_BUTTON = 9;
const WPARAM STEP_BUTTON = 10;

const unsigned buttons_amount = 10;

//
//regs: from 31 to 60
//
const WPARAM R_REGS_IDs[r_regs_amount] = { 31, 32, 33, 34, 35, 36, 37, 38 };

const WPARAM FLAGS_IDs[flags_amount] = { 39, 40, 41, 42, 43, 44 };

const WPARAM BP_REG_ID = 60;
//
//regs descriptions: from 61 to 90
//
const unsigned regs_descr_offset = 30;
const WPARAM R_REGS_DESCR_IDs[r_regs_amount] = 
{ 
	R_REGS_IDs[0] + regs_descr_offset, 
	R_REGS_IDs[1] + regs_descr_offset,
	R_REGS_IDs[2] + regs_descr_offset,
	R_REGS_IDs[3] + regs_descr_offset,
	R_REGS_IDs[4] + regs_descr_offset,
	R_REGS_IDs[5] + regs_descr_offset,
	R_REGS_IDs[6] + regs_descr_offset,
	R_REGS_IDs[7] + regs_descr_offset
};

const WPARAM FLAGS_DESCR_IDs[flags_amount] =
{
	FLAGS_IDs[0] + regs_descr_offset,
	FLAGS_IDs[1] + regs_descr_offset,
	FLAGS_IDs[2] + regs_descr_offset,
	FLAGS_IDs[3] + regs_descr_offset,
	FLAGS_IDs[4] + regs_descr_offset,
	FLAGS_IDs[5] + regs_descr_offset
};

const WPARAM BP_REG_DESCR_ID = BP_REG_ID + regs_descr_offset;




//
//checkboxes: from 91 to 100
//
const WPARAM SYNCHRONIZATION_CHECKBOX = 91;
const WPARAM CACHE_CHECKBOX = 92;
const WPARAM PIPELINE_CHECKBOX = 93;

const unsigned checkboxes_amount = 3;


//
//listboxes: from 101 to 110
//

const WPARAM RAM_LISTBOX = 101;
const WPARAM VRAM_LISTBOX = 102;
const WPARAM ROM_LISTBOX = 103;
const WPARAM IO_LISTBOX = 104;

const unsigned listboxes_amount = 4;

//
//listboxes descriptions: from 111 to 120
//
const unsigned listbox_descr_offset = 10;

const WPARAM RAM_LISTBOX_DESC = RAM_LISTBOX + listbox_descr_offset;
const WPARAM VRAM_LISTBOX_DESC = VRAM_LISTBOX + listbox_descr_offset;
const WPARAM ROM_LISTBOX_DESC = ROM_LISTBOX + listbox_descr_offset;
const WPARAM IO_LISTBOX_DESC = IO_LISTBOX + listbox_descr_offset;

const char flag_strs[flags_amount][2] = { "T", "N", "Z", "V", "C", "I" };


//-------------------------------------------------------------------
//Structs
//-------------------------------------------------------------------
struct gui_item
{
	const char *name;
	int x;
	int y; 
	WPARAM hMenu;
};


const gui_item button_structs[buttons_amount] =
{
	{
		"Run",
		run_x,
		run_y,
		RUN_BUTTON
	},
	{
		"Exit",
		exit_x,
		exit_y,
		EXIT_BUTTON
	},
	{
		"Input",
		input_x,
		input_y,
		INPUT_BUTTON
	},
	{
		"Load exe",
		load_exe_x,
		load_exe_y,
		LOAD_EXE_BUTTON
	},
	{
		"Load mem",
		load_mem_x,
		load_mem_y,
		LOAD_MEM_BUTTON
	},
	{
		"Load regs",
		load_regs_flags_x,
		load_regs_flags_y,
		LOAD_REGS_BUTTON
	},
	{
		"Reset",
		reset_x,
		reset_y,
		RESET_BUTTON
	},
	{
		"Step",
		step_x,
		step_y,
		STEP_BUTTON
	},
	{
		"Stop",
		stop_x,
		stop_y,
		STOP_BUTTON
	},
	{
		"BreakPoint",
		breakpoint_x,
		breakpoint_y,
		BREAKPOINT_BUTTON
	}
};


const gui_item checkbox_structs[checkboxes_amount] =
{
	{
		"synchronization",
		synchronization_x,
		synchronization_y,
		SYNCHRONIZATION_CHECKBOX
	},
	{
		"cache",
		cache_x,
		cache_y,
		CACHE_CHECKBOX
	},
	{
		"pipeline",
		pipeline_x,
		pipeline_y,
		PIPELINE_CHECKBOX
	}
};


const gui_item listbox_structs[listboxes_amount] =
{
	{
		"RAM",
		ram_x,
		ram_y,
		RAM_LISTBOX
	},
	{
		"VRAM",
		vram_x,
		vram_y,
		VRAM_LISTBOX
	},
	{
		"ROM (disasm)",
		rom_x,
		rom_y,
		ROM_LISTBOX
	},
	{
		"IO",
		io_x,
		io_y,
		IO_LISTBOX
	}
};


const gui_item reg_items[r_regs_amount+1] =
{
	{
		"bp",
		reg_x0,
		bp_y,
		BP_REG_DESCR_ID
	},
	{
		"R0",
		reg_x0,
		regs_ys[0],
		R_REGS_DESCR_IDs[0]
	},
	{
		"R1",
		reg_x0,
		regs_ys[1],
		R_REGS_DESCR_IDs[1]
	},
	{
		"R2",
		reg_x0,
		regs_ys[2],
		R_REGS_DESCR_IDs[2]
	},
	{
		"R3",
		reg_x0,
		regs_ys[3],
		R_REGS_DESCR_IDs[3]
	},
	{
		"R4",
		reg_x0,
		regs_ys[4],
		R_REGS_DESCR_IDs[4]
	},
	{
		"R5",
		reg_x0,
		regs_ys[5],
		R_REGS_DESCR_IDs[5]
	},
	{
		"R6",
		reg_x0,
		regs_ys[6],
		R_REGS_DESCR_IDs[6]
	},
	{
		"R7",
		reg_x0,
		regs_ys[7],
		R_REGS_DESCR_IDs[7]
	}
};


const gui_item flag_items[flags_amount] =
{
	{
		flag_strs[0],
		reg_x0,
		flags_ys[0],
		FLAGS_DESCR_IDs[0]
	},
	{
		flag_strs[1],
		reg_x0,
		flags_ys[1],
		FLAGS_DESCR_IDs[1]
	},
	{
		flag_strs[2],
		reg_x0,
		flags_ys[2],
		FLAGS_DESCR_IDs[2]
	},
	{
		flag_strs[3],
		reg_x0,
		flags_ys[3],
		FLAGS_DESCR_IDs[3]
	},
	{
		flag_strs[4],
		reg_x0,
		flags_ys[4],
		FLAGS_DESCR_IDs[4]
	},
	{
		flag_strs[5],
		reg_x0,
		flags_ys[5],
		FLAGS_DESCR_IDs[5]
	}
};