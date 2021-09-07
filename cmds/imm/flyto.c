// flyto.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string home;
	object obj;
	string msg;

	if (! SECURITY_D->valid_grant(me, "(immortal)"))
		return 0;

	if (! arg) return notify_fail("��Ҫ�ɵ��Ķ�ȥ��\n");

	obj = MESSAGE_D->find_user(arg);
	if (! obj) obj = find_living(arg);
	if (! obj || ! me->visible(obj))
		return notify_fail("û�������һ����\n");

	while (obj && obj->is_character())
		obj = environment(obj);

	if (obj == environment(me))
		return notify_fail("����������ǰô���ҷɸ�ɶ��\n");

	if (! obj) return notify_fail("������û�л������� flyto��\n");
	tell_object(me, "�ף���ô��������أ�����\n");
	tell_object(me, "�ǺǺǺǣ����˷��ˣ�СС��ʦ��ѽ�ɡ�����\n");
	if (! me->query("env/invisible"))
		message("vision", me->name() + "��ƮƮ�ķ���������\n",
			environment(me), ({ me }));
	tell_object(me, "���ˣ����ˣ�����ඣ�����\n");
	if (! me->query("env/invisible"))
		message("vision", me->name() + "����������������������\n", obj);
	me->move(obj);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : flyto <Ŀ��>
HELP);
	return 1;
}
