inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "gumu.h"

#define YINSUO    "/clone/weapon/yinsuo"

string ask_yunv();
string ask_me();
string ask_zhen();
mixed ask_yinsuo();

void create()
{
	set_name("С��Ů", ({"long nv", "long"}));
	set("gender", "Ů��");
	set("age", 27);
	set("long",
		"��һ���������£���������������ѩ���������֮�������䣬\n"
		"ʵ��������������¡������ݡ�\n");
	set("attitude", "friendly");

	set("str", 21);
	set("int", 30);
	set("con", 25);
	set("dex", 26);

	set("qi", 3800);
	set("max_qi", 3800);
	set("jing", 1900);
	set("max_jing", 1900);
	set("neili", 4400);
	set("max_neili", 4400);
	set("jiali", 50);

	set("combat_exp", 1600000);
	set("score", 0);

	set_skill("force", 180);
	set_skill("yunv-xinfa", 180);
	set_skill("sword", 180);
	set_skill("yunv-jian", 180);
	set_skill("quanzhen-jian", 170);
	set_skill("whip", 180);
	set_skill("yinsuo-jinling", 180);
	set_skill("dodge", 180);
	set_skill("yunv-shenfa", 180);
	set_skill("parry", 180);
	set_skill("unarmed", 160);
	set_skill("meinv-quan", 160);
	set_skill("strike", 160);
	set_skill("fireice-strike", 160);
	set_skill("tianluo-diwang", 160);
	set_skill("literate", 130);
	set_skill("qufeng", 210);
	set_skill("medical", 200);
	set_skill("yunv-xinjing", 200);
	set_skill("throwing", 200);
	set_skill("yufeng-zhen", 200);
	set_skill("zuoyou-hubo", 250);

	map_skill("force", "yunv-xinfa");
	map_skill("whip", "yinsuo-jinling");
	map_skill("sword", "yunv-jian");
	map_skill("dodge", "yunv-shenfa");
	map_skill("parry", "meinv-quan");
	map_skill("unarmed", "meinv-quan");
	map_skill("strike", "tianluo-diwang");
	map_skill("throwing", "yufeng-zhen");

	prepare_skill("unarmed", "meinv-quan");
	prepare_skill("strike", "tianluo-diwang");

	create_family("��Ĺ��", 3, "����");

	set("book_count", 1);
	set("count", 1);
	set("yfzhen_count", 3);

	set("inquiry", ([
		"����"     : "��������������",
		"���"     : "������������������",
		"�����"   : "�š�����Ƚϸ��ӣ��������Լ�ȥ������������Ҳ���(canwu)�ɡ�",
		"��"       : (: ask_me :),
		"��Ů����" : "��Ů������ȫ�潣���ϱڣ������޵У�\n",
		"��Ů�ľ�" : (: ask_yunv :),
		"�����"   : (: ask_zhen :),
		"��������" : (: ask_yinsuo :),
	]) );

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: perform_action, "strike.wang" :),
		(: perform_action, "sword.he" :),
		(: perform_action, "sword.lian" :),
		(: perform_action, "unarmed.you" :),
	}) );

	setup();

	carry_object("/d/gumu/npc/obj/shunvjian")->wield();
	carry_object("/clone/cloth/baipao")->wear();

}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob) )
		return;

	if (ob->query("per") < 20)
	{
		command("say ����ʵ�ڲ��ҹ�ά���ҿ��㻹�����˰ɡ�\n");
		return;
	}

	command("say �ðɣ��Ҿ����������ͽ���ˡ�\n");
	command("recruit " + ob->query("id"));
}

int recognize_apprentice(object ob, string skill)
{
	return ob->query("family/family_name") == query("family/family_name");
}

string ask_yunv()
{
	object me;
	object ob;
	mapping fam;

	me = this_player();
	if (! (fam = me->query("family")) ||
	    fam["family_name"] != "��Ĺ��")
		return RANK_D->query_respect(me) +
		"�뱾�ɺ��޹ϸ𣬺��������ɵ��ľ���";

	if (this_player()->query_skill("yunv-xinfa", 1) < 15)
		return RANK_D->query_respect(me) +
			"����Ů�ķ����̫ǳ���Ҳ��ܽ���Ů�ľ������㡣";

	if (query("book_count") < 1)
		return "�������ˣ����ɵ���Ů�ľ��Ѿ�����ȡ���ˡ�";

	add("book_count", -1);
	ob = new("/clone/book/yunvjing1");
	ob->move(me, 1);
	return "�ðɣ��Ȿ����Ů�ľ��������ˣ���Ҫ�úÿ�����";
}

string ask_me()
{
	object ob;

	if (query("count") < 1)
		return "��������ͷҲû���ˡ�";

	add("count", -1);
	ob = new("/d/gumu/npc/obj/junzijian");
	ob->move(this_player(), 1);
	return "������ӽ����͸���ɡ�";
}

string ask_zhen()
{
	object me;
	object ob;
	mapping fam;

	me = this_player();
	if (! (fam = me->query("family")) ||
	    fam["family_name"] != "��Ĺ��")
		return RANK_D->query_respect(me) +
		"�뱾�ɺ��޹ϸ𣬺��������ɰ�����";

	if (me->query_skill("yufeng-zhen", 1) < 50)
		return RANK_D->query_respect(me) +
			"��������ַ���򻹲����ң����������Ҳû��ʲô�á�";

	if (query("yfzhen_count") < 1)
		return "�������ˣ�����ͷ��������Ѿ������ˡ�";

	add("yfzhen_count", -1);
	ob = new("/d/gumu/obj/yfzhen");
	message_vision("$N�ó�һЩ�����ݸ�$n��\n", this_object(), me);
	ob->move(me, 1);
	return "�ðɣ���Щ�����������ȥ�ðɡ�";
}

void reset()
{
	set("book_count", 1);
	set("yfzhen_count", 2 + random(2));
}

void unconcious()
{
	die();
}

mixed ask_yinsuo()
{
	object me;
	object ob;
	object owner;

	me = this_player();

	if (me->query("family/family_name") != "��Ĺ��")
		return "�����������ҵ�������������ʲô��ϵ��";

	if (me->query("family/master_id") != query("id"))
		return "ֻ���ҵĵ��Ӳ������������壬�㻹����ذɡ�";

	if (me->query("gender") != "Ů��")
		return "�����������岻�ʺ��㣬����ȥû�á�";

	if (me->query_skill("yinsuo-jinling", 1) < 150)
		return "�����������嶼ûѧ�ã�����Ҳ���ڰ��á�";

	ob = find_object(YINSUO);
	if (! ob) ob = load_object(YINSUO);
	owner = environment(ob);
	while (owner)
	{
		if (owner->is_character() || ! environment(owner))
			break;
		owner = environment(owner);
	}

	if (owner == me)
		return "�ţ��������岻��������������";

	if (objectp(owner) && owner != this_object())
	{
		if (! owner->is_character())
			return "���Ѿ������������Ѿ����ȥ�ˡ�";

		if (owner->query("family/master_id") == query("id"))
			return "�����������������ͬ��" +
			       owner->query("name") + "���ã���Ҫ"
			       "���þ�ȥ�����ɡ�";
		else
			return "����Ϊ���·����أ�������������������"
			       + owner->query("name") + "���У���ȥ"
			       "�����һ����ɡ�";
	}

	ob->move(this_object());
	message_vision(HIC "$N" HIC "΢΢һЦ����������Ȼ������������"
		       "�����������ȥ�ɣ����߽���ʱ��ҪС�ģ������"
		       "Ū���ˣ���"NOR"\n",
		       this_object(), me);
	command("give yinsuo jinling to " + me->query("id"));
	return 1;
}
