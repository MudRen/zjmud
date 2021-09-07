
#include <ansi.h>
inherit F_SSERVER;
void remove_effect(object me, object target, int count, int skill);

string query_name() { return HIG"�����Ի���"NOR; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
        int skill,mp,ap,dp;

        target = offensive_target(me);

        if( !target
         || !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");


        if (me->query_temp("thd/mazed")) 
                return notify_fail("������������˲��������С�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if (me->is_busy())
                return notify_fail("����æ���У���Ͼ����\n");

        if( (int)me->query("neili") < 1000  ) 
                return notify_fail("�������������\n");
        if( (int)me->query("jingli") < 200  ) 
                return notify_fail("��ľ���������\n");
        if( (int)me->query_temp("thd/maze") ) 
                return notify_fail("���Ѿ�����һ�������ˡ�\n");
        if( (int)target->query_temp("thd/mazed") ) 
                return notify_fail(target->name() + "�Ѿ����������ˡ�\n");

        skill = me->query_skill("qimen-wuxing", 1);
        if( skill<150 ) 
                return notify_fail("����������еȼ�����150�����޷������Ի���\n");
        if( (int)me->query_skill("bibo-shengong",1)<150 ) 
                return notify_fail("��ı̲��񹦵ȼ�����150�����޷������Ի���\n");


        me->add("neili", -200+random(300));
        me->add("jingli",-100);

	  mp = me->query_skill("count", 1)/3;
	  ap = me->query_skill("bibo-shengong", 1) + mp + skill;
	  dp = target->query_skill("force",1) + target->query_skill("count", 1)/3 + target->query_skill("qimen-wuxing", 1);

        message_vision(HIY"$NͻȻԾ������һ�ƣ�����һ�ȣ�����Χ��ʯ�顢��֦�ƶ���λ�ã�"NOR"\n", me, target);
        if(random(ap) > dp/2){
        message_vision(HBYEL"$n���������У���ʱ�����޴롣"NOR"\n", me, target);
                target->add_temp("apply/parry", -(skill/10));
                target->add_temp("apply/dodge", -(skill/10));
                target->add_temp("apply/damage", -(skill/10));
                target->set_temp("thd/mazed", 1);
                target->start_busy(4);
                me->start_busy(2);
                me->add_temp("apply/defense", skill/5);
                me->set_temp("thd/maze", skill/5);
                me->set_temp("thd/maze_target", target);
                call_out("remove_effect", 1, me, target, 20, skill);
        }
        else {
		message_vision(HBGRN"$nѸ����ǰ�ˣ�������������������֮�⡣"NOR"\n", me, target);
                me->delete_temp("thd/maze");
                me->delete_temp("thd/maze_target");
                me->start_busy(3);                        
        }
         return 1;
        }
void remove_effect(object me, object target, int count, int skill)
{
        if (objectp(me) && me->query_temp("thd/maze")){
                if (count-- > 0 && me->is_fighting(target)) {
                        call_out("remove_effect", 1, me, target, count, skill);
                        return;
                }
                me->add_temp("apply/defense", - (skill/5));
                me->delete_temp("thd/maze");
                me->delete_temp("thd/maze_target");
                if (!target) return;

                if (target && me->is_fighting(target)) {
                        tell_object(me, "�㲼�������Ѿ���" + target->name() + "�ƻ��ˡ�\n");
                        if (userp(target) && living(target))
                                tell_object(target, me->name() + "���㲼�������Ѿ�����ʶ���ˡ�\n");
                }
                else {
                        tell_object(me, "�㲼�������Ѿ�ʧЧ�ˡ�\n");
                }
        }
        if (objectp(target) && target->query_temp("thd/mazed")){
                target->delete_temp("thd/mazed");
                target->add_temp("apply/parry", skill/10);
                target->add_temp("apply/dodge", skill/10);
                target->add_temp("apply/damage", skill/10);
        }
}

int help(object me)
{
        write(HIG"\n�������Ի��󡹣�"NOR"\n");
        write(@HELP

        ʹ�����Ű���֮�����������Ա̺�����֮�ھ�Ѹ��������֦����ʯ������
        ����һ���ر�Ϊ�̱������׼����������������Ķ��ֲ�������æ�ң�ͬ
        ʱս������Ҳ�ή�ͣ�����ķ�����Ե���ߡ�

        Ҫ��  �̺������ȼ� 150 ���ϣ�
                �������еȼ� 150 ���ϣ�
                ������� 1000 ���ϣ�
                ��������������ֵ��������޷�ʹ�á�
HELP
        );
        return 1;
}

