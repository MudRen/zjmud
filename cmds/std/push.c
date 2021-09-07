// push.c ����

#include <ansi.h>

mapping default_where = ([
	"n":	"north",
	"s":	"south",
	"e":	"east",
	"w":	"west",
	"nu":	"northup",
	"su":	"southup",
	"eu":	"eastup",
	"wu":	"westup",
	"nd":	"northdown",
	"sd":	"southdown",
	"ed":	"eastdown",
	"wd":	"westdown",
	"ne":	"northeast",
	"nw":	"northwest",
	"se":	"southeast",
	"sw":	"southwest",
	"u":	"up",
	"d":	"down",
]);

mapping default_dirs = ([
	"north":	"����",
	"south":	"�ϱ�",
	"east":		"����",
	"west":		"����",
	"northup":	"����",
	"southup":	"�ϱ�",
	"eastup":	"����",
	"westup":	"����",
	"northdown":	"����",
	"southdown":	"�ϱ�",
	"eastdown":	"����",
	"westdown":	"����",
	"northeast":	"����",
	"northwest":	"����",
	"southeast":	"����",
	"southwest":	"����",
	"up":		"����",
	"down":		"����",
	"enter":	"����",
	"out":		"����",
]);

mapping default_undirs = ([
	"south":	"����",
	"north":	"�ϱ�",
	"west":		"����",
	"east":		"����",
	"southup":	"����",
	"northup":	"�ϱ�",
	"westup":	"����",
	"eastup":	"����",
	"southdown":	"����",
	"northdown":	"�ϱ�",
	"westdown":	"����",
	"eastdown":	"����",
	"southwest":	"����",
	"southeast":	"����",
	"northwest":	"����",
	"northeast":	"����",
	"down":		"����",
	"up":		"����",
	"out":		"����",
	"enter":	"����",
]);

int main(object me, string arg)
{
	string who, where, dir, undir, where_temp;
	object env, env_to;
	mapping exits;
	object target;
	string msg;
	int wiz_push;

	if (! SECURITY_D->valid_grant(me, "(immortal)"))
		return 0;

	if (! arg || sscanf(arg, "%s to %s", who, where_temp) != 2) 
		return notify_fail("ָ���ʽ��push <����> to <����>\n");

	env = environment(me);
	if (! env || env->query("no_fight"))
		return notify_fail("���ﲻ�������ŵĵط���\n");

	if (! objectp(target = present(who, env)))
		return notify_fail("��Ҫ�ƿ�˭��\n");

	if (! target->is_character())
		return notify_fail("�����һ�㣬�ǲ��������\n");

	if (target->is_fighting())
		return notify_fail("�˼��������ڴ���أ�����ȥ�ұⰡ��\n");

	if (target->query("doing"))
		return notify_fail("�˼���������ڤ���ù�����̫�ô��ű��˰ɡ�\n");

	if (! living(target))
		return notify_fail("��������û��֪�����㻹�Ƿ����˼��߰ɡ�\n");

	if (! playerp(target))
		return notify_fail("�㿴�˿�����ˣ�û�Ҷ���\n");

	if (! undefinedp(default_where[where_temp]))
		where = default_where[where_temp];
	else
		where = where_temp;

	if (! mapp(exits = env->query("exits")) || undefinedp(exits[where]))
		return notify_fail("û���������\n");

	if (! objectp(env_to = find_object(exits[where])))
	{
		call_other(exits[where], "???");
		env_to = find_object(exits[where]);
	}

	wiz_push = wiz_level(me) >= wiz_level("(wizard)");

	if (! wiz_push)
	{
		if (me->query("qi", 1) < 150)
			return notify_fail("���������ѣ��Ʋ������ˡ�\n");
	
		if (me->query("neili", 1) < 100)
			return notify_fail("���������ã��Ʋ������ˡ�\n");
	
		if (me->query_skill("force") < 100)
			return notify_fail("���ڹ���Ϊ���ޣ�û�е���������صĵز���\n");
	}

	if (! undefinedp(default_dirs[where]))
		dir = default_dirs[where];
	else
		dir = where;

	if (! undefinedp(default_undirs[where]))
		undir = default_undirs[where];
	else
		undir = where;

	switch (random(3))
	{
	case 0:
		msg = "$N���һ�����ȵ������ÿ��ˣ�����˳�ƾͰ�$n��" +
		      dir + "һ����\n";
		break;

	case 1:
		msg = "$N������üͷ���յ������������������ְ�$n��" +
		      dir + "һ�ơ�\n";
		break;

	default:
		msg = "$N˫Ŀһ�ɣ��ȵ�������������������������˵�հ�$n��" +
		      dir + "��ȥ��\n";
		break;
	}

	if (! wiz_push)
	{
		me->receive_damage("qi", 100);
		me->add("neili", -50);
	}

	if (wiz_level(me) < wiz_level(target))
		msg += "$N���������ƣ�ֻ���ú���ײ����һ��ǽһ����\n";
	else
	if (! wiz_push && target->query_skill("force") >= 150)
		msg += "$NĬ��������ȴ����$n�ڹ�������Ϊ��ʵ����һ�¾�Ȼû�к����Է������ɵ�һ㶡�\n";
	else
	{
		if (! env->valid_leave(target, where))
		{
			message_vision(msg, me, target);
			write("����ȥ�����Ʋ����˼ҡ�\n");
			return 1;
		}

		if (! target || environment(target) != env)
		{
			message_vision(msg, me, target);
			write("����ˣ����أ�\n");
			return 1;
		}

		msg += "ֻ��$N��һ�°�$n�������ࡱ�����˿�ȥ��\n";
		message_vision(msg, me, target);
		target->move(env_to);
		message("vision", "ֻ��" + target->name() + "����ײײ�Ĵ�" +
				  undir + "���˹�����\n", env_to, target);
		if (! target->is_busy())
			target->stary_busy(5);
		return 1;
	}
	
	message_vision(msg, me, target);
	if (! me->is_busy())
		me->start_busy(1);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : push <����> to <����>

���ָ������Ѿ��÷���������ƿ�����Ȼ�������˼��ڹ���ʵ��
����һ���Ӷ���಻��Ч��
HELP );
	return 1;
}
