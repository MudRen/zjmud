// smash.c 2-22-95
 
#include <ansi.h>

inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
	object ob;
	int immortal;
	string msg;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg)
		return notify_fail("ָ���ʽ: smash <living>\n");

	ob = present(arg, environment(me));
	if (! ob || ! me->visible(ob))
	{
		ob = find_player(arg);
		if (! ob || wiz_level(ob) < 1 || ! me->visible(ob))
			ob = find_living(arg);

		if (! ob || ! me->visible(ob))
			ob = find_object(arg);

		if (! ob || ! ob->is_character() || ! me->visible(ob))
			return notify_fail("�Ҳ���������\n");
	}

	if (! me->is_admin())
	{
		switch (SECURITY_D->query_site_privilege("smash"))
		{
		case "all":
			break;

		case "npc":
			if (playerp(ob))
				return notify_fail("�㲻�ܶ����ʩչ������\n");
			break;

		default:
			return notify_fail("�㲻��ʹ�ø����\n");
		}
	}

	if (environment(ob) != environment(me))
	{
		message("vision", HIY "\n��������İ�����������Ȼ�����һ����һ����������������ֱ����£���������" +
				  ob->name(1) + HIY "��"NOR"\n", all_interactive());
		
		if (wizardp(ob))
		{
			immortal = (int)ob->query("env/immortal");
			ob->set("env/immortal", 0);
		}
	
		if (wiz_level(me) < wiz_level(ob))
		{
			message_vision(HIM "\n$N" HIM "����ð���������̣�"
				       "ȴû�а�����顣"NOR"\n",
				       ob);
			return 1;
		}
	
		ob->set_temp("die_reason", "��" + me->name(1) + "����������");
	
		ob->receive_damage("qi", 1, me);
		ob->die();
		if (ob && wizardp(ob))
			ob->set("env/immortal", immortal);
		return 1;
	}

	msg = HIC "\n$N" HIC "����һ�У�ֻ��һ��" HIY "����" HIC
	      "���������������$n" HIC "������"NOR"\n";
	if (me == ob)
	{
		msg = replace_string(msg, "$n", "$N");
		message_vision(msg, me);
	}
	else
		message_vision(msg, me, ob);

	if (! ob->is_character())
	{
		message_vision(HIM + ob->name() + HIM "�������������ʧ��...\n\n"
			       NOR, me);
		destruct(ob);
		return 1;
	}

	if (wizardp(ob))
	{
		immortal = (int)ob->query("env/immortal");
		ob->set("env/immortal", 0);
	}

	if (wiz_level(me) < wiz_level(ob))
	{
		message_vision(HIM "\n$N" HIM "����ð���������̣�"
			       "ȴû�а�����顣"NOR"\n",
			       ob);
		return 1;
	}

	ob->set_temp("die_reason", "����������");

	if (ob == me)
	       ob->set_temp("die_reason", "��ò��ͷ������װ��Լ�������");

	ob->receive_damage("qi", 1, me);
	ob->die();
	if (ob && wizardp(ob))
		ob->set("env/immortal", immortal);

	return 1;
}
 
int help(object me)
{
	write(@HELP
ָ���ʽ: smash <����>
 
hehehehehe...........

�������ڿ��Ա���Ȩʹ�õ���Ϣ������npc��all��
HELP );
	return 1;
}
