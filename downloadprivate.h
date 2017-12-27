#ifndef DOWNLOADPRIVATE_H
#define DOWNLOADPRIVATE_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2018 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */


#define DOWNLOAD_DECLARE_PRIVATE(Class) \
    friend class Class##Private; \
    DownloadPrivateInterface<Class, Class##Private> Download_d;

#define DOWNLOAD_DECLARE_PUBLIC(Class) \
    friend class Class;

#define DOWNLOAD_INIT_PRIVATE \
    Download_d.setPublic(this);

#define DOWNLOAD_D(Class) Class##Private *const d = Download_d()
#define DOWNLOAD_Q(Class) Class *const q = Download_q()

template <typename PUB>
/*! @brief The class of the Download private base.
 * @author Greedysky <greedysky@163.com>
 */
class DownloadPrivate
{
public:
    virtual ~DownloadPrivate() { }
    inline void setPublic(PUB* pub) { Download_q_ptr = pub; }

protected:
    inline PUB *Download_q() const { return Download_q_ptr; }

private:
    PUB* Download_q_ptr;

};

template <typename PUB, typename PVT>
/*! @brief The class of the ttk private interface.
 * @author Greedysky <greedysky@163.com>
 */
class DownloadPrivateInterface
{
    friend class DownloadPrivate<PUB>;
public:
    DownloadPrivateInterface() { pvt = new PVT; }
    ~DownloadPrivateInterface() { delete pvt; }

    inline void setPublic(PUB* pub) { pvt->setPublic(pub); }
    inline PVT *operator()() const { return static_cast<PVT*>(pvt); }

private:
    DownloadPrivateInterface(const DownloadPrivateInterface&) { }
    DownloadPrivateInterface& operator=(const DownloadPrivateInterface&) { }
    DownloadPrivate<PUB>* pvt;

};


#endif // DOWNLOADPRIVATE_H
