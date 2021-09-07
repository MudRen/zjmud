// learn_fly.c ��������
#include <ansi.h>

inherit NPC;
inherit F_DEALER;
string ask_fly();
void create()
{
	set_name("��������", ({"xian ren"}));
	set("age", 32);
	set("gender", "����");
	set("title", "��������");
	set("long", "�����������µ����ˣ����ڱ��������ڡ� ������ ����\n");
	set("attitude", "friendly");
	set("str", 30);
	set("skill_fly", 1);
	set("dex", 30);
	set("combat_exp", 40000000);
	set("shen_type", 1);
	set("chat_chance",1);
	set_skill("fly", 600);  //������
	set("inquiry", ([
	    "������" : (: ask_fly :),
	]));
	setup();
}

void init()
{
}
string ask_fly()
{
	return "�ҿ��Խ���< ������ >����Ҫ�Ƚ� ��ʮ ������!\n";
}
void greeting(object ob)
{
	if (! ob || environment(ob) != environment())
		return;

	say("��������ˬ�ʵ�˵�����ɷ�����ѧϰ< ������ >��\n");
}
int recognize_apprentice(object ob)
{
	if (ob->query_temp("mark/������") < 1)
		return 0;

	ob->add_temp("mark/������", -1);
	return 1;
}

int accept_object(object who, object ob)
{
	if (! who->query_temp("mark/������"))
		who->set_temp("mark/������", 0);

	if (ob->query("money_id") && ob->value() >= 2000)
	{
		message_vision(HIG"��������ͬ��ָ��$NһЩ[ ������ ]�ϵ����⡣"NOR"\n", who);
		who->add_temp("mark/������", ob->value() / 50);
		destruct(ob);
		return 1;
	}

	command("say �����ѧ�棬���[ ������ ]����Ҫ��ʮ��������");
	return 0;
}

