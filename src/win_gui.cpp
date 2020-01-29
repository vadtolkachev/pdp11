#include "win_gui.hpp"


MainWindow::MainWindow(pdp11 *the_pdp11):
    m_hScreen(NULL),
    m_hCacheCheckbox(NULL),
    m_hSyncCheckbox(NULL),
    m_hPipelineCheckbox(NULL),
    m_hRegs{},
    m_hFlags{},
    m_hBP(NULL),

    m_hRAMListBox(NULL),
    m_hVRAMListBox(NULL),
    m_hROMListBox(NULL),
    m_hIOListBox(NULL),
    m_hBmp(NULL),

    m_pdp11(the_pdp11)
{}


PCWSTR MainWindow::ClassName() const
{
    return pdp11_window_class_name;
}


LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
        handle_create();
        break;


    case WM_KEYDOWN:
        handle_keydown(wParam);
        return DefWindowProc(m_hMainWnd, msg, wParam, lParam);
        break;

    case WM_COMMAND:
        handle_command(wParam);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(m_hMainWnd, msg, wParam, lParam);
    }

    return 0;
}


pdp11 *MainWindow::get_pdp11()
{
    return m_pdp11;
}


void MainWindow::upd_proc_state(const uint16_t regs[8], const status_flags flags, const uint8_t flag_I, const uint16_t bp)
{
    char buffer[64];
    const char bool_vals[2][2] = {"0", "1"};

    // go with regs
    for (uint8_t i = 0; i < r_regs_amount; i++)
    {
        sprintf_s(buffer, 64, "%06o", regs[i]);
        SetWindowTextA(m_hRegs[i], buffer);
    }


    //go with bp
    sprintf_s(buffer, 64, "%06o", bp);
    SetWindowTextA(m_hBP, buffer);


    //go with flags
    SetWindowTextA(m_hFlags[0], bool_vals[flags.T]);
    SetWindowTextA(m_hFlags[1], bool_vals[flags.N]);
    SetWindowTextA(m_hFlags[2], bool_vals[flags.Z]);
    SetWindowTextA(m_hFlags[3], bool_vals[flags.V]);
    SetWindowTextA(m_hFlags[4], bool_vals[flags.C]);

    sprintf_s(buffer, "%u", flag_I);
    SetWindowTextA(m_hFlags[5], buffer);
}


void MainWindow::print_disasm(char str_arr[ROM_size / 2][100])
{
    SendMessage(m_hROMListBox, WM_SETREDRAW, FALSE, 0L);
    SendMessage(m_hROMListBox, LB_RESETCONTENT, 0, 0);

    for(int i = 0; i < ROM_size / 2; i++)
    {
        SendMessageA(m_hROMListBox, LB_ADDSTRING, 0,
            (LPARAM)str_arr[i]);
    }

    SendMessage(m_hROMListBox, WM_SETREDRAW, TRUE, 0L);
    InvalidateRect(m_hROMListBox, NULL, TRUE);
}


void MainWindow::print_memory(char str_arr1[RAM_size / 2][100], char str_arr2[VRAM_size / 2][100], char str_arr3[IO_size / 2][100])
{
    print_RAM(str_arr1);
    print_VRAM(str_arr2);
    print_IO(str_arr3);
}


void MainWindow::print_RAM(char str_arr[RAM_size / 2][100])
{
    SendMessage(m_hRAMListBox, WM_SETREDRAW, FALSE, 0L);
    SendMessage(m_hRAMListBox, LB_RESETCONTENT, 0, 0);

    for(int i = 0; i < RAM_size / 2; i++)
    {
        SendMessageA(m_hRAMListBox, LB_ADDSTRING, 0,
            (LPARAM)str_arr[i]);
    }

    SendMessage(m_hRAMListBox, WM_SETREDRAW, TRUE, 0L);
    InvalidateRect(m_hRAMListBox, NULL, TRUE);
}


void MainWindow::print_VRAM(char str_arr[VRAM_size / 2][100])
{
    SendMessage(m_hVRAMListBox, WM_SETREDRAW, FALSE, 0L);
    SendMessage(m_hVRAMListBox, LB_RESETCONTENT, 0, 0);

    for(int i = 0; i < VRAM_size / 2; i++)
    {
        SendMessageA(m_hVRAMListBox, LB_ADDSTRING, 0,
            (LPARAM)str_arr[i]);
    }

    SendMessage(m_hVRAMListBox, WM_SETREDRAW, TRUE, 0L);
    InvalidateRect(m_hVRAMListBox, NULL, TRUE);
}


void MainWindow::print_IO(char str_arr[IO_size / 2][100])
{
    SendMessage(m_hIOListBox, WM_SETREDRAW, FALSE, 0L);
    SendMessage(m_hIOListBox, LB_RESETCONTENT, 0, 0);

    for(int i = 0; i < IO_size / 2; i++)
    {
        SendMessageA(m_hIOListBox, LB_ADDSTRING, 0,
            (LPARAM)str_arr[i]);
    }

    SendMessage(m_hIOListBox, WM_SETREDRAW, TRUE, 0L);
    InvalidateRect(m_hIOListBox, NULL, TRUE);
}


void MainWindow::add_controls()
{
    //screen
    m_hScreen = CreateWindowExA(0L, "Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP | WS_BORDER, 
        pdp_win_x, pdp_win_y, pdp_win_width, pdp_win_height,
        m_hMainWnd, NULL, NULL, NULL);

    //buttons
    for(int i = 0; i < buttons_amount; i++)
    {
        create_button(&button_structs[i]);
    }

    //checkboxes
    m_hSyncCheckbox = create_checkbox(&checkbox_structs[0]);
    m_hCacheCheckbox = create_checkbox(&checkbox_structs[1]);
    m_hPipelineCheckbox = create_checkbox(&checkbox_structs[2]);

    //bp
    m_hBP = create_reg_item(&reg_items[0]);

    //regs
    for(uint8_t i = 0; i < r_regs_amount; i++)
    {
        m_hRegs[i] = create_reg_item(&reg_items[1+i]);
    }

    //flags 
    for(uint8_t i = 0; i < flags_amount; i++)
    {
        m_hFlags[i] = create_flag_item(&flag_items[i]);
    }
    

    // listboxes
    m_hRAMListBox = create_listbox(&listbox_structs[0]);
    m_hVRAMListBox = create_listbox(&listbox_structs[1]);
    m_hROMListBox = create_listbox(&listbox_structs[2]);
    m_hIOListBox = create_listbox(&listbox_structs[3]);
}


void MainWindow::DrawPixels(void *pixels)
{
    m_hBmp = CreateBitmap(512, 512, 1, 32, pixels);
    SendMessageW(m_hScreen, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBmp);
}


bool MainWindow::gui_open_file(char *out_str)
{
    OPENFILENAMEA ofn;

    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = m_hMainWnd;
    ofn.lpstrFile = out_str;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "Text files\0*.txt\0";
    ofn.nFilterIndex = 1;

    return GetOpenFileNameA(&ofn);
}


void MainWindow::create_button(const gui_item *str)
{
    CreateWindowExA(0L, "Button", str->name, WS_VISIBLE | WS_CHILD,
        str->x, str->y, button_width, button_height,
        m_hMainWnd, (HMENU)str->hMenu, NULL, NULL);
}


HWND MainWindow::create_checkbox(const gui_item *str)
{
    return CreateWindowExA(0L, "button", str->name,
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        str->x, str->y, checkbox_width, checkbox_height,
        m_hMainWnd, (HMENU)str->hMenu, NULL, NULL);
}


HWND MainWindow::create_listbox(const gui_item *str)
{
    CreateWindowExA(0L, "static", str->name,
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        str->x, str->y, desc_box_width, desc_box_height,
        m_hMainWnd, (HMENU)(str->hMenu + listbox_descr_offset), NULL, NULL);

    int listbox_y = static_cast<int>(str->y + desc_box_height + list_descr_offset);
    return CreateWindowExA(0L, "listbox", NULL,
        WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_WANTKEYBOARDINPUT,
        str->x, listbox_y, list_box_width, list_box_height,
        m_hMainWnd, (HMENU)str->hMenu, NULL, NULL);
}


HWND MainWindow::create_reg_item(const gui_item *str)
{
    CreateWindowExA(0L, "static", str->name,
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        str->x, str->y, reg_descr_width, reg_descr_height,
        m_hMainWnd, (HMENU)str->hMenu, NULL, NULL);

    
    return CreateWindowExA(0L, "static", "000000",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            str->x + reg_descr_offset_x, str->y, reg_width, reg_height,
            m_hMainWnd, (HMENU)(str->hMenu - regs_descr_offset), NULL, NULL);
}


HWND MainWindow::create_flag_item(const gui_item *str)
{
    CreateWindowExA(0L, "static", str->name,
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        str->x, str->y, reg_descr_width, reg_descr_height,
        m_hMainWnd, (HMENU)str->hMenu, NULL, NULL);


    return CreateWindowExA(0L, "static", "0",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        str->x + reg_descr_offset_x, str->y, reg_width, reg_height,
        m_hMainWnd, (HMENU)(str->hMenu - regs_descr_offset), NULL, NULL);
}


void MainWindow::handle_create()
{
    add_controls();
}


void MainWindow::handle_keydown(WPARAM wParam)
{
    uint8_t key_code = 0;

    key_code = static_cast<uint8_t>(wParam);
    m_pdp11->set_key_code(key_code);

    m_pdp11->do_job(pdp_job_type::IRQ01);
}


void MainWindow::handle_command(WPARAM wParam)
{
    switch(LOWORD(wParam))
    {
    //buttons
    case RUN_BUTTON:
        handle_run_button();
        break;

    case EXIT_BUTTON:
        handle_exit_button();
        break;

    case STEP_BUTTON:
        handle_step_button();
        break;

    case STOP_BUTTON:
        handle_stop_button();
        break;

    case INPUT_BUTTON:
        handle_input_button();
        break;

    case LOAD_EXE_BUTTON:
        handle_load_exe_button();
        break;

    case LOAD_MEM_BUTTON:
        handle_load_mem_button();
        break;

    case LOAD_REGS_BUTTON:
        handle_load_regs_button();
        break;

    case RESET_BUTTON:
        handle_reset_button();
        break;

    case BREAKPOINT_BUTTON:
        handle_breakpoint_button();
        break;

    
    //checkboxes
    case SYNCHRONIZATION_CHECKBOX:
        handle_synchronization_checkbox();
        break;

    case CACHE_CHECKBOX:
        handle_cache_checkbox();
        break;

    case PIPELINE_CHECKBOX:
        handle_pipeline_checkbox();
        break;


    //listboxes
    case ROM_LISTBOX:
        handle_rom_listbox(wParam);
        break;


    default:
        break;
    }
}


void MainWindow::handle_run_button()
{
    VRet checkErr = m_pdp11->do_job(pdp_job_type::RUN);
    if(checkErr != VRet::VSUCCESS)
    {
        if(checkErr == VRet::VFAILURE)
            MessageBoxW(GetConsoleWindow(), L"Pdp-11 is already running.", 0, MB_ICONSTOP | MB_TASKMODAL);
        else
            MessageBoxW(GetConsoleWindow(), L"The task is already queued up.", 0, MB_ICONINFORMATION | MB_TASKMODAL);
    }
}


void MainWindow::handle_exit_button()
{
    VRet checkErr = m_pdp11->do_job(pdp_job_type::EXIT);
    if(checkErr != VRet::VSUCCESS)
    {
        MessageBoxW(GetConsoleWindow(), L"Pdp-11 is already running.", 0, MB_ICONSTOP | MB_TASKMODAL);
        return;
    }

    DestroyWindow(m_hMainWnd);
}


void MainWindow::handle_step_button()
{
    /*VRet checkErr = the_pdp11->do_job(pdp_job_type::STEP);
    if(checkErr != VRet::VSUCCESS)
    {
        MessageBoxW(GetConsoleWindow(), L"Pdp-11 is already running.", 0, MB_ICONSTOP | MB_TASKMODAL);
        return 0;
    }*/
}


void MainWindow::handle_stop_button()
{
    VRet checkErr = m_pdp11->do_job(pdp_job_type::STOP);
    if(checkErr != VRet::VSUCCESS)
        MessageBoxA(GetConsoleWindow(), "Pdp-11 is not running.", 0, MB_ICONSTOP | MB_TASKMODAL);
}


void MainWindow::handle_input_button()
{
    MessageBoxA(GetConsoleWindow(), "\tinput\t\t", "input", MB_ICONINFORMATION | MB_TASKMODAL);
}


void MainWindow::handle_load_exe_button()
{
    VRet checkErr = m_pdp11->do_job(pdp_job_type::LOAD);
    if(checkErr != VRet::VSUCCESS)
        MessageBoxA(GetConsoleWindow(), "Pdp-11 is already running.", 0, MB_ICONSTOP | MB_TASKMODAL);
}


void MainWindow::handle_load_mem_button()
{
    m_pdp11->load_mem();
}


void MainWindow::handle_load_regs_button()
{
    m_pdp11->load_regs();
}


void MainWindow::handle_reset_button()
{
    VRet checkErr = m_pdp11->do_job(pdp_job_type::RESET);
    if(checkErr != VRet::VSUCCESS)
        MessageBoxA(GetConsoleWindow(), "Pdp-11 is already running.", 0, MB_ICONSTOP | MB_TASKMODAL);
}


void MainWindow::handle_breakpoint_button()
{
    VRet checkErr = m_pdp11->set_bp();
    if(checkErr != VRet::VSUCCESS)
    {
        MessageBoxA(GetConsoleWindow(), "Select failure", 0, MB_ICONSTOP | MB_TASKMODAL);
        return;
    }

    m_pdp11->load_regs();
}


void MainWindow::handle_synchronization_checkbox()
{
    LRESULT res = SendMessage(m_hSyncCheckbox, BM_GETCHECK, 0, 0);

    if(res == BST_CHECKED)
    {
        sync_on(m_pdp11);
    }
    if(res == BST_UNCHECKED)
    {
        sync_off(m_pdp11);
    }
}


void MainWindow::handle_cache_checkbox()
{
    LRESULT res = SendMessage(m_hCacheCheckbox, BM_GETCHECK, 0, 0);

    if(res == BST_CHECKED)
    {
        cache_mem_on(m_pdp11);
    }
    if(res == BST_UNCHECKED)
    {
        cache_mem_off(m_pdp11);
    }
}


void MainWindow::handle_pipeline_checkbox()
{
    LRESULT res = SendMessage(m_hPipelineCheckbox, BM_GETCHECK, 0, 0);

    if(res == BST_CHECKED)
    {
        conv_on(m_pdp11);
    }
    if(res == BST_UNCHECKED)
    {
        conv_off(m_pdp11);
    }
}


void MainWindow::handle_rom_listbox(WPARAM wParam)
{
    LRESULT count;
    uint16_t iSelected;

    switch(HIWORD(wParam))
    {
    case LBN_SELCHANGE:
        count = SendMessage(m_hROMListBox, LB_GETCOUNT, 0, 0);
        iSelected = 0;

        // go through the items and find the first selected one
        for(LRESULT i = 0; i < count; i++)
        {
            // check if this item is selected or not..
            if(SendMessage(m_hROMListBox, LB_GETSEL, static_cast<WPARAM>(i), 0) > 0)
            {
                // yes, we only want the first selected so break.
                iSelected = static_cast<uint16_t>(i);
                break;
            }
        }

        m_pdp11->set_selected(iSelected);
        break;
    }
}
