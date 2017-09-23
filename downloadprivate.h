#ifndef DOWNLOADPRIVATE_H
#define DOWNLOADPRIVATE_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/


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
