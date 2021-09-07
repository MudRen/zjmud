// repairv.c					  
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	mixed  msg;
	int consistence;
	int cost;

	if (! arg)
		return notify_fail("��Ҫ����ʲô������\n");

	if (me->is_busy())
		return notify_fail("��������æ���أ�\n");

	if (!me->query("zjvip/times"))
		return notify_fail("�ǻ�Ա������������װ����\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("�����Ϻ���û������������\n");

	if (undefinedp(consistence = ob->query("consistence")))
		return notify_fail(ob->name() + "�ƺ�����Ҫ����������ɣ�\n");

	if (consistence >= 100)
		return notify_fail(ob->name() + "�����������������ʲô��\n");

	if (! undefinedp(msg = ob->query("no_repair")))
	{
		if (stringp(msg))
			write(msg);
		else
			write("�ⶫ���޷�����\n");
		return 1;
	}

	cost = ob->query("magic/power")+ob->query("point")+ob->level_now(1)*30;
	if(cost<80) cost = 80;
	cost *= 1000;
	cost = (100 - consistence)*cost/100;

	if (MONEY_D->player_pay(me, cost) != 1)
		return notify_fail("�����ϵ�Ǯ����"+MONEY_D->price_str(cost)+"���������װ����\n");

	ob->set("consistence", 100);
	me->start_busy(1);

	tell_object(me, YEL "�㻨��"+MONEY_D->price_str(cost)+"�������"+ob->name()+NOR"��\n");
	return 1;
}

int help(object me)
{
     write(@HELP
ָ���ʽ: 

���ָ������û�Ա��������װ����

HELP
    );
    return 1;
}
