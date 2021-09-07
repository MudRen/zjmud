// drive.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

mapping dirs = ([
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
]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	string cdir, rdir;
	string dir;
	object env;
	string msg_leave, msg_arrival;
	int lvl;
	int result;

	if (! arg)
		return notify_fail("��Ҫ��ʲô��\n");

	if (sscanf(arg, "%s %s", arg, dir) != 2)
		return notify_fail("��Ҫ���ĸ�����ϣ�\n");

	if (! objectp(ob = present(arg, environment(me))))
		return notify_fail("����û��������������ϰ���\n");

	notify_fail("�㿴����ˣ��ⲻ������ʹ�ĳ�����\n");
	if (! ob->can_drive_by(me))
		return 0;

	if (! undefinedp(dirs[dir]))
		dir = dirs[dir];
	else
	if (member_array(dir, values(dirs)) == -1)
		return notify_fail("�㲻�����������ϳ���\n");

	if (me->is_fighting())
		return notify_fail("���������ں��˼Ҷ��֣�û�ոϳ���\n");

	if (me->is_busy())
		return notify_fail("����һ��������û����ɣ��ȵȵȰɡ�\n");

	// �鿴�ݳ�����
	lvl = me->query_skill("driving");
	if (random(lvl + 100) < 50)
	{
		message_vision("$N��æ���ҵ������˰��죬����" +
			       ob->name() + "һ��������\n", me);
		me->start_busy(1);
		return 1;
	}

	env = environment(me);

	notify_fail("");
	result = GO_CMD->main(me, dir);
	if (environment(me) == env)
	{
		string fail;

		if (! result)
		{
			fail = query_fail_msg();
		} else
			fail = "";
		write(fail + "������û������" + ob->name() + "ǰ����\n");
		return 1;
	}
	ob->move(environment(me));

	if (random(lvl + 100) < 30)
		me->start_busy(1);

	if (me->can_improve_skill("driving"))
		me->improve_skill("driving", 1);

	cdir = GO_CMD->query_chinese_dir(dir);
	dir  = GO_CMD->query_reverse(dir);
	rdir = GO_CMD->query_chinese_dir(dir);
	switch (random(5))
	{
	case 0:
		msg_leave   = "$Nһ��ߺ�ȣ�����$n��" + cdir + "ʻȥ��\n";
		msg_arrival = "ֻ��һ��ߺ�ȣ�$N����$n��" + rdir + "ʻ����\n";
		break;
	case 1:
		msg_leave   = "$Nһ�Բ�����ֻ�Ǹ���$n��" + cdir + "ʻȥ��\n";
		msg_arrival = "ֻ��$N��ͷ���Եĸ���$n��" + rdir + "ʻ�˹�����\n";
		break;
	case 2:
		msg_leave   = "$N�ȵ������ÿ��ˣ��ÿ��ˡ���ֻ���˺�$n�Ѿ���������" +
			      rdir + "ȥ�ˡ�\n";
		msg_arrival = "ԶԶ��ֻ��һ������������žͼ�$N����$n�����Ĵ�" +
			      rdir + "ʻ�˹�����\n";
		break;
	case 3:
		msg_leave   = "$NĨ��Ĩ������������$n��" + rdir + "ȥ�ˡ�\n";
		msg_arrival = "ֻ��$Nһ��Ĩ����һ�߸���$n��" +
			      rdir + "ʻ�˹�����\n";
		break;
	default:
		msg_leave   = "ֻ��¡¡���죬�ͼ�$N�����ĸ���$n��" +
			      rdir + "ȥ�ˡ�\n";
		msg_arrival = "ֻ��¡¡���죬�ͼ�$N�����ĸ���$n��" +
			      rdir + "ʻ����\n";
		break;
	}

	msg_leave = replace_string(msg_leave, "$N", me->name());
	msg_leave = replace_string(msg_leave, "$n", ob->name());
	msg_arrival = replace_string(msg_arrival, "$N", me->name());
	msg_arrival = replace_string(msg_arrival, "$n", ob->name());

	message("vision", msg_leave, env);
	message("vision", msg_arrival, environment(me), ({ me }));
	tell_object(me, "�����" + ob->name() +
			"����" + environment(me)->short() + "��\n");
	ob->set_owner(me);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : drive <����> <����>
 
���ָ�����������ĳ������ϳ�����Ȼ���������ĳ����С����
��ļݳ��������Ƿǳ���죬��ô���ܲ������ɵ���ʹ�������п���
���������Ҫ���ӳ١���ô�����Լ��ļݳ����������������
 
HELP );
    return 1;
}
