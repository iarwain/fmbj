/**
 * @file fmbj.h
 * @date 31-May-2021
 */

#ifndef __fmbj_H__
#define __fmbj_H__

#define __NO_SCROLLED__
#include "Scroll.h"

/** Game Class
 */
class fmbj : public Scroll<fmbj>
{
public:


private:

                orxSTATUS       Bootstrap() const;

                void            Update(const orxCLOCK_INFO &Info);

                orxSTATUS       Init();
                orxSTATUS       Run();
                void            Exit();
                void            BindObjects();


private:
};

#endif // __fmbj_H__
