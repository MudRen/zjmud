// zui.c �޺����

#include <ansi.h>

#define PFM_NAME	"�޺����"

inherit F_SSERVER;

string query_name() { return "�޺�"ZJBR"���"; }

int perform(object me, object target)
{
	string msg;
	int count;
	int skill;
 
	if ((int)me->query("neili") < 150)
		return notify_fail("�������������ʩչ��" + PFM_NAME + "����\n");

	if ((int)me->query_temp("zui-quan_zui"))
		return notify_fail("���Ѿ���������������ˡ�\n");
	
	if ((int)me->query_skill("zui-quan", 1) < 80)
		return notify_fail("�����ȭ�������ң��޷�ʩչ��" + PFM_NAME + "����\n");

	msg = HIY "$N" HIY "��������һ�䣬˫ȭ���գ�ʹ��һ�С�" + PFM_NAME +
	      HIY "������������֡�\n"
	      HIG "���Ʋ������ģ���̬�ɾУ�������ȴ���֮����"NOR"\n";

	message_combatd(msg, me);
	me->add("neili", -100);

	skill = me->query_skill("zui-quan", 1);
	count = 3 + random(5);
	me->add_temp("dex", count);
	me->start_call_out((: call_other, __FILE__, "remove_effect",
			   me, count :), skill / 3);

	me->set_temp("zui-quan_zui", 1);

	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("zui-quan_zui"))
	{
		me->add_temp("dex", -amount);
		me->delete_temp("zui-quan_zui");
		tell_object(me, "����޺�����˹���ϣ��������ջص��\n");
	}
}
