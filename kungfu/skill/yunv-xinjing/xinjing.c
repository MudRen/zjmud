// powerup.c ��Ů�ķ�����

#include <ansi.h>
inherit F_CLEAN_UP;

string *pictures=({
  HIY"��˼��"YEL"���"HIC"������"HIR"���¡�"HIB"���"MAG"��Ц"HIW,
  YEL"�ٳ"CYN"���֡�"HIG"��ϲ��"HIR"��ŭ��"HIY"�ٺá�"RED"�ٶ�"HIW,
  HIC"��˼"HIG"��"HIW"�񵡣�"HIB"����"MAG"��"HIY"��ɢ"HIW,
  HIR"����"YEL"��"BLU"����"MAG"����"RED"��"HIG"��ƣ"HIW,
  HIB"����"CYN"��"RED"���٣�"HIR"��Ц"HIC"��"BLU"����"HIW,
  MAG"���"YEL"��"HIR"���壬"RED"����"BLU"��"HIY"����"HIW,
  HIW"��ϲ"HIG"��"HIY"����"MAG"���ң�"HIC"��ŭ"HIR"��"HIB"����"HIG"����"HIW,
  HIG"���"RED"��"BLU"ר��"HIG"���Σ�"HIW"���"HIB"��"MAG"����"CYN"����"HIW
});

void remove_effect(object me, int amount);

string query_name() { return "��Ů"ZJBR"�ľ�"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;
        string picture;

	if (target != me)
		return notify_fail("��ֻ�������Լ���ս������\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	if ((int)me->query_skill("yunv-xinjing",1) < 120)
		return notify_fail("�����Ů�ľ����������졣\n");

	skill = me->query_skill("force");

        picture = pictures[random(sizeof(pictures))];
        message_vision(HIY"$N�������񣬿���Ĭ��"HIW"��"+picture+"��"HIY"����Ů�ľ�����Ҫ����"NOR"\n", me);

//	message_combatd(HIC "$N" HIC "��ɫ΢΢һ����˫������һ�֣�������"
//			"���һ��" HIW "��������" HIC "ʢ���ڳ����ĺ����У�"NOR"\n", me);

	me->add_temp("apply/attack", skill / 4);
	me->add_temp("apply/dodge", skill / 4);
	me->add_temp("apply/defense", skill / 4);
	me->set_temp("powerup", 1);
	me->add("neili", -100);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 4 :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
	if (me->query_temp("powerup"))
	{
		me->add_temp("apply/attack", -amount);
		me->add_temp("apply/dodge", -amount);
		me->add_temp("apply/defense", -amount);
		me->delete_temp("powerup");
		tell_object(me, "�����Ů�ľ�������ϣ��������ջص��\n");
	}
}
