// wash.c

#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string target;
	object dest;
	string msg;
	int remain;

	if (!arg)
		return notify_fail("��Ҫϴʲô��\n");

	target = arg;

	if (! environment(me)->query("resource/water"))
		return notify_fail("����ûˮ������ôϴ��\n");

	if (me->is_busy())
		return notify_fail("��æ�������������ϴ�ɣ�\n");

	if (me->is_fighting())
		return notify_fail("�㻹�Ǵ����˼���ϴ�ɣ�\n");

	if (target == "hand" || target == "me")
	{
		// washing me
		dest = me;
	} else
	{
		dest = present(target, me);
		if (! dest) dest = present(target, environment(me));
		if (! dest)
			return notify_fail("����û������������\n");

		if (dest->is_character())
		{
			if (dest != me)
			{
				write("��Ҫ���˼�" + dest->name() + "ϴ�裿\n");
				return 1;
			}
			// daub on me
		} else
		if (! mapp(dest->query("armor_prop")) &&
		    ! mapp(dest->query("weapon_prop")))
		{
			return notify_fail("�ǼȲ���������Ҳ���Ƿ��ߣ�"
					   "����ʲô����ϴ�ģ�\n");
		}
	}

	if (remain = dest->query_temp("daub/poison/remain"))
	{
		if (remain > 10000)
			msg = "��ֻ��ϴ���ˮ����ȳ��ޱȣ������ڱǡ�\n";
		else
		if (remain > 4000)
			msg = "���ͼ���ˮ���ı�����ɫ���������ģ���ζ�Ź֡�\n";
		else
		if (remain > 1000)
			msg = "����ˮ�漴ɫ�䣬ɢ����һ�����ŵ���ζ��\n";
		else
			msg = "��ϴ��ˮ����ɫ����е㲻�ԡ�\n";
	} else
		msg = "��\n";

	dest->delete_temp("daub");
	if (dest == me)
	{
		message_vision("$N�úõ�ϴ��ϴ��" + msg, me);
		return 1;
	}

	if (dest->query("equipped") == "worn")
	{
		function f;

		if (! REMOVE_CMD->do_remove(me, dest))
			return 0;

		if (! dest || ! me)
			return 1;

		message_vision("$N����������$n�úõ�ϴ��ϴ" + msg, me, dest);
		dest->washed(120 + random(120));
		return 1;
	}

	message_vision("$N�ó�$n���úõ�ϴ��ϴ" + msg, me, dest);
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : wash <����> | <����> | hand

���ָ��������㽫���������ߺúó�ϴһ�£����������Ķ�����Ȼû��
����ϴ��Ҳ����ʲô���¡�
HELP
    );
    return 1;
}
