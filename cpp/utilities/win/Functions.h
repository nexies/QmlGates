#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Windows.h>
#include <Commctrl.h>
#include <shlobj.h>  // Для создания нового ShellView
#include <winuser.h>


HWND CreateListView (HWND hwndParent)
{
    INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    RECT rcClient;                       // The parent window's client area.

    GetClientRect (hwndParent, &rcClient);

    // Create the list-view window in report view with label editing enabled.
    HWND hWndListView = CreateWindow(WC_LISTVIEW,
                                     "",
                                     WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
                                     0, 0,
                                     rcClient.right - rcClient.left,
                                     rcClient.bottom - rcClient.top,
                                     hwndParent,
                                     NULL,
                                     (HINSTANCE)GetWindowLong(hwndParent, GWL_HINSTANCE),
                                     NULL);

    return (hWndListView);
}
VOID SetView(HWND hWndListView, DWORD dwView)
{
    // Retrieve the current window style.
    DWORD dwStyle = GetWindowLong(hWndListView, GWL_STYLE);

    // Set the window style only if the view bits changed.
    if ((dwStyle & LVS_TYPEMASK) != dwView)
    {
        SetWindowLong(hWndListView,
                      GWL_STYLE,
                      (dwStyle & ~LVS_TYPEMASK) | dwView);
    }               // Logical OR'ing of dwView with the result of
}                   // a bitwise AND between dwStyle and
// the Unary complenent of LVS_TYPEMASK.
BOOL InitListViewColumns(HWND hWndListView, int C_COLUMNS, int FirstColumn)
{
    LPSTR szText[256];     // Temporary buffer.
    LVCOLUMN lvc;
    int iCol;

    // Initialize the LVCOLUMN structure.
    // The mask specifies that the format, width, text,
    // and subitem members of the structure are valid.
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    // Add the columns.
    for (iCol = 0; iCol < C_COLUMNS; iCol++)
    {
        lvc.iSubItem = iCol;
        lvc.pszText = (LPSTR)szText;
        lvc.cx = 100;               // Width of column in pixels.

        if ( iCol < 2 )
            lvc.fmt = LVCFMT_LEFT;  // Left-aligned column.
        else
            lvc.fmt = LVCFMT_RIGHT; // Right-aligned column.

        // Load the names of the column headings from the string resources.
        LoadString((HINSTANCE)GetWindowLong((HWND)GetWindowLong(hWndListView,GWL_HWNDPARENT),GWL_HINSTANCE),
                   FirstColumn + iCol,
                   (LPSTR)szText,
                   sizeof(szText)/sizeof(szText[0]));

        // Insert the columns into the list view.
        if (ListView_InsertColumn(hWndListView, iCol, &lvc) == -1)
            return FALSE;
    }

    return TRUE;
}
BOOL InsertListViewItems(HWND hWndListView, LPSTR text, LPVOID iImage)
{
    LVITEM lvI;

    // Initialize LVITEM members that are common to all items.
    lvI.pszText   = text; // Sends an LVN_GETDISPINFO message.
    lvI.cchTextMax= strlen(text);
    lvI.mask      = LVIF_TEXT | LVIF_IMAGE |LVIF_STATE;
    lvI.stateMask = 0;
    lvI.iSubItem  = 0;
    lvI.state     = 0;
    int index=ListView_GetItemCount(hWndListView)+1;
    lvI.iItem  = index;
    lvI.iImage = (int)iImage;

    // Insert items into the list.
    if (ListView_InsertItem(hWndListView, &lvI) == -1)
        return FALSE;

    return TRUE;
}
BOOL InitListViewImageLists(HWND hWndListView, LPVOID IDI_ITEM, HINSTANCE hInstance)
{
    HICON hiconItem;     // Icon for list-view items.
    HIMAGELIST hLarge;   // Image list for icon view.
    HIMAGELIST hSmall;   // Image list for other views.

    // Create the full-sized icon image lists.
    hLarge = ImageList_Create(GetSystemMetrics(SM_CXICON),
                              GetSystemMetrics(SM_CYICON),
                              ILC_MASK, 1, 1);

    hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
                              GetSystemMetrics(SM_CYSMICON),
                              ILC_MASK, 1, 1);

    // Add an icon to each image list.
    hiconItem = LoadIcon(hInstance,(LPCTSTR)IDI_ITEM);

    ImageList_AddIcon(hLarge, hiconItem);
    ImageList_AddIcon(hSmall, hiconItem);

    DestroyIcon(hiconItem);


    // Assign the image lists to the list-view control.
    ListView_SetImageList(hWndListView, hLarge, LVSIL_NORMAL);
    ListView_SetImageList(hWndListView, hSmall, LVSIL_SMALL);

    return TRUE;
}

// hWnd[1] = CreateListView((HWND)hWnd[0]);
// InitListViewImageLists((HWND)hWnd[1], NULL, NULL);
// SetView((HWND)hWnd[1], LVS_ICON);
// InitListViewColumns((HWND)hWnd[1], 1, IDS_FIRSTCOLUMN);
// InsertListViewItems((HWND)hWnd[1], "Windows", NULL);



void ToggleDesktopIcons(bool hide) {
    HWND hProgman = FindWindow(L"Progman", NULL);
    if (!hProgman) return;

    HWND hDefView = FindWindowEx(hProgman, NULL, L"SHELLDLL_DefView", NULL);
    if (!hDefView) {
        HWND hWorkerW = FindWindowEx(NULL, NULL, L"WorkerW", NULL);
        while (hWorkerW) {
            hDefView = FindWindowEx(hWorkerW, NULL, L"SHELLDLL_DefView", NULL);
            if (hDefView) break;
            hWorkerW = FindWindowEx(NULL, hWorkerW, L"WorkerW", NULL);
        }
    }

    if (hDefView) {
        HWND hSysListView32 = FindWindowEx(hDefView, NULL, L"SysListView32", NULL);
        if (hSysListView32) {
            ShowWindow(hSysListView32, hide ? SW_HIDE : SW_SHOW);
        }
    }
}

#endif // FUNCTIONS_H
