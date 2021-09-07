// yin.c ����ͤ

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

mixed ask_me();

void create()
{
	set_name("����ͤ", ({ "yin liting", "yin" }));
	set("nickname", "�䵱����");
	set("long", 
		"�����������������������ͤ��\n"
		"��������ʮ�꣬�����ܸɣ�������������һ�\n");
	set("gender", "����");
	set("age", 30);
	set("attitude", "heroism");
	set("shen_type", 1);
	set("str", 26);
	set("int", 30);
	set("con", 26);
	set("dex", 28);
	
	set("max_qi", 4200);
	set("max_jing", 2100);
	set("neili", 4800);
	set("max_neili", 4800);
	set("jiali", 100);
	set("combat_exp", 1250000);
	set("score", 45000);

	set_skill("force", 165);
	set_skill("wudang-xinfa", 165);
	set_skill("taiji-shengong", 165);
	set_skill("dodge", 175);
	set_skill("tiyunzong", 175);
	set_skill("unarmed", 170);
	set_skill("taiji-quan", 170);
	set_skill("strike", 165);
	set_skill("wudang-zhang", 165);
	set_skill("hand", 180);
	set_skill("paiyun-shou", 180);
	set_skill("parry", 175);
	set_skill("sword", 160);
	set_skill("wudang-jian", 160);
	set_skill("raozhi-roujian", 180);
	set_skill("taiji-jian", 160);
	set_skill("taoism", 120);
	set_skill("literate", 100);

	set("no_teach", ([
		"taiji-shengong" : "Ҫ��ѧϰ̫����������������̡�",
		"taiji-jian"     : "̫���������������״���",
		"taiji-quan"     : "̫��ȭ�����������״���",
	]));

	map_skill("force", "wudang-xinfa");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "wudang-jian");
	map_skill("sword", "raozhi-roujian");
	map_skill("strike", "wudang-zhang");

	prepare_skill("unarmed", "taiji-quan");
	prepare_skill("strike", "wudang-zhang");

	create_family("�䵱��", 2, "����");

	set("inquiry", ([
		"���´���": (: ask_me :),
		"����"  : (: ask_me :),
	]));

	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: perform_action, "sword.chuankong" :),
		(: exert_function, "recover" :),
	}) );

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query("shen") < 8000)
	{
		command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
			"�Ƿ����ò�����");
		return;
	}

	if ((int)ob->query_skill("wudang-xinfa", 1) < 70)
	{
		command("say ���䵱����ע���ڹ��ķ�" + RANK_D->query_respect(ob)+
			"�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��?");
		return;
	}

	if ((int)ob->query_skill("taoism", 1) < 70)
	{
		command("say ϰ����Ϊ��ǿ���壬һζ�������ǲ���ȡ�ġ�");
		command("say �ҿ��㻹��Ҫ���������Է�����������������"
			"����ĵ����ķ���");
		return;
	}

	command("say �ðɣ��Ҿ��������ˡ�");
	command("say ϣ�����ܺú��ù�������аħ�����");
	command("recruit " + ob->query("id"));
	if( (string)ob->query("class") != "taoist")
		ob->set("class", "taoist");
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/raozhi-roujian/chuankong"))
		return "�Լ��úö���ϰ�ɣ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

	if (me->query("shen") < 15000)
		return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

	if (me->query_skill("raozhi-roujian", 1) < 110)
		return "�����ָ�ὣ�������ң�Ҫ��������";

	message_vision(HIY "$n" HIY "���˵�ͷ���γ����䳤��ͻȻ��$N" HIY
		       HIY "������;�н������䣬�Ǳ��������Ƴ���һ��"
		       "��\n�����������ۣ�Ʈ��������������ʮ���С���ָ"
		       "�ὣ�������һ�С����´��ա���"NOR"\n",
		       me, this_object());
	command("nod");
	command("say ��������ˣ�");
	tell_object(me, HIC "��ѧ���ˡ����´��ա���һ�С�"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 160000);
	me->set("can_perform/raozhi-roujian/chuankong", 1);
	return 1;
}
