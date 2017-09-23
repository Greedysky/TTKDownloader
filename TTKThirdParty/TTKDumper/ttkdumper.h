#ifndef TTKDUMPER_H
#define TTKDUMPER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadextrasglobaldefine.h"

class MiniDumper;

/*! @brief The class of the ttk dumper.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_EXTRAS_EXPORT TTKDumper
{
public:
    /*!
     * Object contsructor.
     */
    TTKDumper();
    ~TTKDumper();

    /*!
     * Run.
     */
    void run();

protected:
    MiniDumper *m_winDump;

};

#endif // TTKDUMPER_H
