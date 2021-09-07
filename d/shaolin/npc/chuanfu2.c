// Npc: /d/shaolin/npc/chuanfu2.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����", ({ "chuan fu", }));
	set("long", "���ǳ����ں�ˮר�Źܻ��˵�һλ����\n");

	set("gender", "����");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("age", 42);

	set("inquiry", ([
		"�ڶ�" : "���ۻ�����٣�һ��ʮ�������������ۡ�",
		"����" : "���ۻ�����٣�һ��ʮ�������������ۡ�",
	]));

	setup();
}

int accept_object(object who, object ob)
{
	object *obs;

	obs = filter_array(all_inventory(environment(who)),
			   (: $1->query_temp("owner") == $(who) :));

	if (sizeof(filter_array(obs, (: ! $1->is_character() :))) < 1)
	{
		message_vision("�������һ����$N������������ˣ������"
			       "ֻ�ܻ��ˣ�û�л�����ʲô�ң���\n", who);
		return 0;
	}

    	if (ob->query("money_id") && ob->value() >= 1000)
	{
		message_vision("������˵�" + ob->name() + "����$N˵���ã�����ϴ��ɣ�\n" , who);
		message_vision("��������������ᴬ�򣬰�$N�������ϴ���һ������ê�����Ϳ����ˡ�\n", who);
		who->move("/d/shaolin/hanshuim");
		if (sizeof(obs)) obs->move("/d/shaolin/hanshuim");
		tell_object(who, HIG "�����е�վ�ڴ�ͷ���λ����ƵĹ��˺�ˮ......"NOR"\n");
		who->start_call_out((: call_other, __FILE__, "goto_peer", who, obs :), 10);
		destruct(ob);
		return -1;
	} else  
		message_vision("�������$Nһ��˵�������Ǯ�����˰ɣ���\n", who);

	return 0;
}

void goto_peer(object ob, object *obs)
{
	if (arrayp(obs) && sizeof(obs))
	{
		obs -= ({ 0 });
		if (sizeof(obs))
			obs->move("/d/shaolin/hanshui1");
	}

	if (! objectp(ob) || environment(ob) != find_object("/d/shaolin/hanshuim"))
		return;

   	tell_object(ob, "�����ڵ��˶԰��������´��������ϵĻ�ƽ���Ļ�������������\n");
   	ob->move("/d/shaolin/hanshui1");
}

void unconcious()
{
	::die();
}
