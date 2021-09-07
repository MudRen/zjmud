
#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "̫��"ZJBR"ս��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ����̫�����������Լ���ս������\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "Ĭ��̫���������������������������پ�"
                        "ȫ���Ȼ�������᲻�ɴݡ�"NOR"\n", me);
        //��ͨ�ζ�������Ч��
        
        if (me->query("breakup"))
        {    
                me->add_temp("apply/attack", skill / 3);      
        }
        else
        {
                me->add_temp("apply/attack", skill / 6);
        }
	  me->add_temp("apply/unarmed_damage", skill/6);
        me->set_temp("powerup", 1);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill/2);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
                if (me->query("breakup"))
                {
                        me->add_temp("apply/attack", - (amount / 3));
                }
                else
                {
                        me->add_temp("apply/attack", - (amount / 6)); 
                }
	          me->add_temp("apply/unarmed_damage", -amount/6);
                me->delete_temp("powerup");
                tell_object(me, "���̫����������ϣ��������ջص��\n");
        }

}


