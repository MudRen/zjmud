// inherit object: knower.c
// ��Ϣ��ͨ��ʿ�̳д˶���

#include <ansi.h>

inherit NPC;

int is_knower() { return 1; }

// ���մ�����Ϣ
mixed accept_ask(object ob, string topic)
{
	return QUEST_D->generate_information(this_object(), ob, topic);
}

int accept_hit(object me)
{
	command("say ���ۣ���... ��...");
	return -1;
}

int accept_fight(object me)
{
	command("say С�Ŀɲ��Һ�" + RANK_D->query_respect(me) + "���С�");
	return -1;
}

int accept_kill(object me)
{
	return notify_fail("�㰵�룺�Ժ����˻�����Щ�ô������Ҳ�æ���֡�\n");
}

int accept_ansuan(object me)
{
	return notify_fail("�������ʱ�����׵�������óȻ���֡�\n");
}

int accept_touxi(object me)
{
	return notify_fail("����öԷ����Ǿ��裬�������֡�\n");
}

varargs int receive_damage(string type, int points, object who)
{
	return 0;
}

varargs int receive_wound(string type, int points, object who)
{
	return 0;
}

void unconcious()
{
	die();
}

varargs void die()
{
	mapping my;
	message_vision("$N���ۡ��Ĵ����һ����\n", this_object());
	my = query_entire_dbase();
	my["qi"] = my["eff_qi"] = my["max_qi"];
	my["jing"] = my["eff_jing"] = my["max_jing"];
}
