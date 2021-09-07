// reply.c

#include <ansi.h>
#include <command.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string target, mud;
	object obj;
	string no_tell, can_tell;
	string reply_out;

	if (! arg || arg == "")
		return notify_fail("��Ҫ�ش�ʲô��\n");

	if (! stringp(target = me->query_temp("reply")) )
		return notify_fail("�ղ�û���˺���˵������\n");

	if (sscanf(target, "%s@%s", target, mud) == 2)
	{
		GTELL->send_gtell(lower_case(mud), lower_case(target), me, arg);
		write("��·ѶϢ���ͳ�������Ҫ�Ժ���ܵõ���Ӧ��\n");
		return 1;
	}

	obj = find_player(target);
	if (! obj || ! me->visible(obj))
	{
		if (MESSAGE_D->send_msg_to(me, target, arg))
			return 1;
		return notify_fail("�ղź���˵�����������Ѿ��뿪��Ϸ�ˡ�\n");
	}

	no_tell = obj->query("env/no_tell");
	if (! wizardp(me) && (no_tell == "all" || no_tell == "ALL" ||
	    is_sub(me->query("id"), no_tell)))
	{
		can_tell = obj->query("env/can_tell");
		if (! is_sub(me->query("id"), can_tell))
			return notify_fail("����˲���������������\n");
	}

	if (playerp(obj) && obj->is_net_dead())
		return notify_fail("��������ڲ������ϣ���������Ļ���\n");

	if (! living(obj))
		return notify_fail("�������ڿ�����������˵�Ļ���...\n");

	reply_out = sprintf(HIG "%s�ش��㣺%s"NOR"\n",
			    me->name(1) + HIG "(" + me->query("id") + ")", arg);
	if (! TELL_CMD->notice_user(me->name(1), me->query("id"), obj, reply_out))
		return 1;

	// �ɹ��Ļش���
	write(HIG "��ش�" + obj->name(1) + HIG + "(" + obj->query("id") +
	      ")��" + arg + ""NOR"\n");

	if (query_idle(obj) >= 120)
		write(YEL "����" + obj->name(1) +
		      YEL "�Ѿ�����Ȧ�з�����" + chinese_number(query_idle(obj) / 60) +
		      "�����ˣ�����û��������Ļ���\n");

	// ���ѡ��Ĳ���ȫ����(2)�����Զ�����������Ϣ����ʾ
	// ��һ����Ϣ��
	if (me->query("env/jam_talk") != 2)
		SKIP_CMD->main(me, "");

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��reply <ѶϢ>

����������ָ��͸ղ��� tell ����˵����ʹ����˵�����ڶ��˺�
�㽻̸��ʱ���������ͨ��������ô���ã���Ϊ�п������� reply
��ʱ�����������㷢����Ϣ��������Ӧ���������������������
���ò���jam_talk��ѡ������ʽ��̸���������ʾ�� >  ����ɫ���
��ɫ��ʱ����ζ���������յ������˷��͸���Ľ�̸��Ϣ��

see also : tell��skip
HELP );
	return 1;
}
