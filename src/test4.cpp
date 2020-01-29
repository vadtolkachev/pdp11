#include "pdp11.hpp"
#include "win_gui.hpp"
#include "miniasm.hpp"

/*
const char txt_file1[] = "../res/1.txt";
const char txt_file2[] = "../res/2.txt";
const char txt_file3[] = "../res/3.txt";
const char txt_file4[] = "../res/4.txt";
const char txt_file5[] = "../res/5.txt";
const char txt_file6[] = "../res/6.txt";
const char txt_file7[] = "../res/7.txt";
const char txt_file8[] = "../res/8.txt";
const char txt_file9[] = "../res/9.txt";
const char txt_file10[] = "../res/10.txt";
const char txt_file15[] = "../res/15.txt";

const char bin_file1[] = "../res/1.bin";

const char *target_txt = txt_file6;
const char *targer_bin = bin_file1;
*/
const PortSolver solver;

FILE *dbg_log_file = nullptr;
FILE *pdp_log_file = nullptr;


void pdp_start();


DWORD WINAPI pdp_thread_function(void *ptr) noexcept;
DWORD WINAPI video_thread_function(void *ptr) noexcept;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(nShowCmd);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(hInstance);

    /*
    pdp_display_controller d_contr;
    d_contr.unzip_font(font8x8_basic);
    return EXIT_SUCCESS;
    */

    dbg_log_file = solver.fopen_dbg("log_file.txt", "w");
    
    pdp_start();

    DBG_PRINTF("EXIT_SUCCESS\n");
    solver.fclose_dbg(dbg_log_file);
    
    return EXIT_SUCCESS;
}



void pdp_start()
{
    pdp11 the_pdp11;

    MainWindow the_main_window(&the_pdp11);

    the_pdp11.set_main_window(&the_main_window);

    if(!the_main_window.create_main_wnd())
        assert(false);

    ShowWindow(the_main_window.getMainWnd(), SW_SHOW);

    DWORD pdp_threadId;
    DWORD video_threadId;
    HANDLE hPdp = CreateThread(NULL, 0, pdp_thread_function, reinterpret_cast<void *>(&the_pdp11), 0, &pdp_threadId);
    HANDLE hVideo = CreateThread(NULL, 0, video_thread_function, reinterpret_cast<void *>(&the_main_window), 0, &video_threadId);

    MSG msg = {};
    BOOL bRet;
    while((bRet = GetMessage(&msg, nullptr, 0, 0)) != 0)
    {
        if(bRet == -1)
        {
            solver.perror("GetMessage: bRet = -1");
            assert(false);
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if(hPdp)
    {
        WaitForSingleObject(hPdp, INFINITE);
        CloseHandle(hPdp);
    }

    if(hVideo)
    {
        WaitForSingleObject(hVideo, INFINITE);
        CloseHandle(hVideo);
    }
}


DWORD WINAPI pdp_thread_function(void *ptr) noexcept
{
    pdp11 *the_pdp11 = reinterpret_cast<pdp11 *>(ptr);
    assert(the_pdp11);
    the_pdp11->start();

    return 0;
}


DWORD WINAPI video_thread_function(void *ptr) noexcept
{
    MainWindow *the_main_window = reinterpret_cast<MainWindow *>(ptr);
    pdp11 *the_pdp11 = the_main_window->get_pdp11();
    assert(the_main_window);

    v_rgb pixels[512 * 512] = {};

    pdp_display_controller d_controller;
    d_controller.set_controller(the_pdp11, pixels);

    while(!the_pdp11->should_exit())
    {
        d_controller.process_buff();

        the_main_window->DrawPixels(pixels);
        
        Sleep(15);
    }

    return 0;
}
