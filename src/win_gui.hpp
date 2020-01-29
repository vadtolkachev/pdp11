#pragma once
#include "defines.hpp"
#include "event_controller.hpp"


const wchar_t pdp11_window_class_name[] = L"myWndClass";


template <class DERIVED_TYPE>
class BaseWindow
{
public:
    BaseWindow();

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND getMainWnd();
    BOOL create_main_wnd();


protected:
    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hMainWnd;
};


class MainWindow: public BaseWindow<MainWindow>
{
public:
    MainWindow(pdp11 *the_pdp11);

    PCWSTR ClassName() const;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    pdp11 *get_pdp11();

    void DrawPixels(void *pixels);
    bool gui_open_file(char *out_str);

    void upd_proc_state(const uint16_t regs[8], const status_flags flags, const uint8_t flag_I, const uint16_t bp);
    void print_disasm(char str_arr[ROM_size / 2][100]);
    void print_memory(char str_arr1[RAM_size / 2][100], char str_arr2[VRAM_size / 2][100], char str_arr3[IO_size / 2][100]);
    void print_RAM(char str_arr[RAM_size / 2][100]);
    void print_VRAM(char str_arr[VRAM_size / 2][100]);
    void print_IO(char str_arr[IO_size / 2][100]);


private:
    void add_controls();

    void create_button(const gui_item *str);
    HWND create_checkbox(const gui_item *str);
    HWND create_listbox(const gui_item *str);
    HWND create_reg_item(const gui_item *str);
    HWND create_flag_item(const gui_item *str);

    void handle_create();
    void handle_keydown(WPARAM wParam);
    void handle_command(WPARAM wParam);

    void handle_run_button();
    void handle_exit_button();
    void handle_step_button();
    void handle_stop_button();
    void handle_input_button();
    void handle_load_exe_button();
    void handle_load_mem_button();
    void handle_load_regs_button();
    void handle_reset_button();
    void handle_breakpoint_button();

    void handle_synchronization_checkbox();
    void handle_cache_checkbox();
    void handle_pipeline_checkbox();

    void handle_rom_listbox(WPARAM wParam);


    HWND m_hScreen;
    HWND m_hCacheCheckbox;
    HWND m_hSyncCheckbox;
    HWND m_hPipelineCheckbox;
    HWND m_hRegs[r_regs_amount];
    HWND m_hFlags[flags_amount];
    HWND m_hBP;

    HWND m_hRAMListBox;
    HWND m_hVRAMListBox;
    HWND m_hROMListBox;
    HWND m_hIOListBox;
    HBITMAP m_hBmp;

    pdp11 *m_pdp11;
};


#include "win_gui_defs.hpp"