#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "codestd.h"
#include "pin.h"
#include "motor.h"

static void motor_isr(motor_id id, uint16_t cstep)
{

}

/**************************************************************************************************

 * @param : 0成功, 其他失败
***************************************************************************************************/
int main(int argc, char const *argv[])
{
    LOG_I("pid = %d", getpid());

    get_motor_ops()->init(motor_isr);
    /* code */
    return 0;
}

