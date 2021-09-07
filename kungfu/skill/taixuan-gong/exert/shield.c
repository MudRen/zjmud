
#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "̫��"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
        int skill = me->query_skill("force") /4 ;

        if (target != me)
                return notify_fail("��ֻ����̫�����������Լ��ķ�������\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if (skill < 40)
                return notify_fail("���̫�����ȼ�������\n");

        if ((int)me->query_temp("shield"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        me->add("neili", -100);
        me->receive_damage("qi", 0);

        message_vision(HIG "$N" HIG "ĬĬ�˹����������͵�ʯ���ϵĿھ�һһ"
                        "���֣�̫�����ھ��ѻ���ȫ��"NOR"\n", me);

        if (me->query("breakup"))
        {
				me->add_temp("apply/dodge", skill);
				me->add_temp("apply/parry", skill);
                        me->add_temp("apply/armor", skill);
        }
        else
        {
				me->add_temp("apply/dodge", skill / 2);
				me->add_temp("apply/parry", skill / 2);
                        me->add_temp("apply/armor", skill / 2);
        }
        me->set_temp("shield", 1);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("shield"))
        {
                if (me->query("breakup")) {
                                    me->add_temp("apply/armor", -amount);
						me->add_temp("apply/dodge", -amount);
						me->add_temp("apply/parry", -amount);
                }
                else {               
                                    me->add_temp("apply/armor", -amount / 2);
						me->add_temp("apply/dodge", -amount / 2);
						me->add_temp("apply/parry", -amount / 2);
                }
		    me->delete_temp("shield");
                tell_object(me, "���̫����������ϣ��������ջص��\n");
        }
       
}


