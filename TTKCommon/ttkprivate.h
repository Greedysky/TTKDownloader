#ifndef TTKPRIVATE_H
#define TTKPRIVATE_H

/***************************************************************************
 * This file is part of the TTK Library Module project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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
 ***************************************************************************/

#include "ttkglobaldefine.h"

#define TTK_CREATE_PRIVATE(Class) (*new Class##Private)

#define TTK_DECLARE_PRIVATE(Class) \
    friend class Class##Private; \
    TTKPrivateInterface<Class, Class##Private> ttk_d;

#define TTK_DECLARE_PUBLIC(Class) \
    friend class Class;

#define TTK_INIT_PRIVATE(Class) \
    ttk_d.setPrivate(new Class##Private); \
    ttk_d.setPublic(this);

#define TTK_INIT_PRIVATE_D(PVT) \
    ttk_d.setPrivate(&PVT); \
    ttk_d.setPublic(this);

#define TTK_D(Class) Class##Private *const d = TTKStaticCast(Class##Private*, ttk_d())
#define TTK_Q(Class) Class *const q = TTKStaticCast(Class*, ttk_q())

template <typename PUB>
/*! @brief The class of the ttk private base.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT TTKPrivate
{
public:
    TTKPrivate()
        : m_qptr(nullptr)
    {

    }

    virtual ~TTKPrivate()
    {

    }

    inline void setPublic(PUB* pub)
    {
        m_qptr = pub;
    }

protected:
    inline PUB *ttk_q() const
    {
        return m_qptr;
    }

private:
    PUB* m_qptr;

};


template <typename PUB, typename PVT>
/*! @brief The class of the ttk private interface.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT TTKPrivateInterface
{
    friend class TTKPrivate<PUB>;
public:
    TTKPrivateInterface()
        : m_dptr(nullptr)
    {

    }

    TTKPrivateInterface(PVT* pvt)
        : m_dptr(pvt)
    {

    }

    ~TTKPrivateInterface()
    {
        delete m_dptr;
    }

    inline void setPrivate(PVT* pvt)
    {
        delete m_dptr;
        m_dptr = pvt;
    }

    inline void setPublic(PUB* pub)
    {
        m_dptr->setPublic(pub);
    }

    inline PVT *operator()() const
    {
        return TTKStaticCast(PVT*, m_dptr);
    }

private:
    TTKPrivate<PUB>* m_dptr;
    TTK_DISABLE_COPY(TTKPrivateInterface)

};

#endif // TTKPRIVATE_H
