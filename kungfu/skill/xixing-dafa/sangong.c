// sangong.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��ɢ"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	if (me->query("max_neili") < 1)
		return notify_fail("���Ѿ�������ɢ����ûʲô��Ҫ��ɢ���ˡ�\n");

	tell_object(target, HIY "��ĬĬ�İ������Ǵ󷨵ľ��Ͻ�����ɢ���澭������"NOR"\n");
	message("vision", HIY + me->name() + "�������أ�ȴ�ֲ������˵���"
			  "�ӣ���֪��������ʲô�����Ĺ���"NOR"\n",
		environment(me), ({ me }));

	me->start_busy(1);
	me->add("max_neili", -1);

	return 1;
}

void del_sucked(object me)
{
	me->delete_temp("sucked");
}
