// divorce.c

#include <room.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object witness;
	mapping couple;
	object  user;
	string  msg;

	seteuid(getuid());

	if (! mapp(couple = me->query("couple")))
		return notify_fail("�����ں����ǵ���һ�˰ɣ�\n");

	if (! arg)
		return notify_fail("��Ҫ��˭�����Լ��\n");

	if (arg == me->query("id"))
		return notify_fail("����...����ķ���...\n");

	if (arg != me->query("couple/id"))
		return notify_fail("���˺������ڲ����Ƿ��޹�ϵ����\n");

	if (objectp(witness = present("marriage witness", environment(me))))
		return witness->do_divorce(me);

	if (! me->query_temp("pending/want_divorce"))
	{
		write("���������֤����˶�û�У�����ݲݵ�����"
		      "���ˣ�Ҫ�����������������һ�����ָ���ʾ���ġ�\n");
		me->set_temp("pending/want_divorce", 1);
		return 1;
	}

	write("���¶����ģ�һ��Ҫ��" + me->query("couple/name") + "���׷��֣�\n");

	CHANNEL_D->do_channel(me, "chat",
		"��" + me->name(1) + "�ӽ�����ͺ�" + couple["name"] +
		"(" + couple["id"] + ")���׶Ͼ���ϵ��");

	user = find_player(couple["id"]);
	if (user)
	{
		switch (user->query("character"))
		{
		case "��������":
			msg = "���ģ�" + me->name(1) + "����û�����ĵ�" +
			      RANK_D->query_rude(me) + "��";
			break;

		case "������":
			msg = "��..�ߣ��٣��߰ɣ��߰ɣ�";
			break;

		case "�ĺ�����":
			msg = "�����" + me->name(1) + "�����������ƣ�";
			break;

		default:
			msg = "�ܺã�" + me->name(1) + "����Űɣ�";
			break;
		}
            //��¼���ʱ��
		user->set("divorce_time", time());
	      me->set("divorce_time", time());
		CHANNEL_D->do_channel(user, "chat", msg);
	}

	UPDATE_D->clear_user_data(me->query("id"), "couple");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : divorce
 
��顣��˼�����Ժ���߸���·��
 
see also : divorce
HELP );
    return 1;
}
