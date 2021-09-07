// yu.c ������

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_me();

void create()
{
	set_name("������", ({ "yu lianzhou", "yu" }));
	set("nickname", "�䵱����");
	set("long", 
		"������������Ķ����������ۡ�\n"
		"��������ʮ�꣬��Ŀ��࣬�������ء�\n"
		"�����䵱�����������ڶ�������ȴ�����\n");
	set("gender", "����");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 32);
	set("dex", 32);
	
	set("max_qi", 4800);
	set("max_jing", 2400);
	set("neili", 5500);
	set("max_neili", 5500);
	set("jiali", 100);
	set("combat_exp", 1600000);
	set("score", 50000);

	set_skill("force", 195);
	set_skill("wudang-xinfa", 195);
	set_skill("taiji-shengong", 195);
	set_skill("dodge", 170);
	set_skill("tiyunzong", 170);
	set_skill("unarmed", 180);
	set_skill("taiji-quan", 180);
	set_skill("strike", 180);
	set_skill("wudang-zhang", 180);
	set_skill("hand", 180);
	set_skill("paiyun-shou", 180);
	set_skill("claw", 180);
	set_skill("huzhua-shou", 180);
	set_skill("parry", 180);
	set_skill("sword", 185);
	set_skill("wudang-jian", 185);
	set_skill("taiji-jian", 185);
	set_skill("taoism", 160);
	set_skill("literate", 100);
	set_skill("medical", 160);
	set_skill("liandan-shu", 160);

	set("no_teach", ([
		"taiji-shengong" : "Ҫ��ѧϰ̫����������������̡�",
		"taiji-jian"     : "̫���������������״���",
		"taiji-quan"     : "̫��ȭ�����������״���",
	]));

	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("hand", "paiyun-shou");
	map_skill("claw", "huzhua-shou");
	map_skill("parry", "taiji-quan");
	map_skill("sword", "taiji-jian");
	map_skill("strike", "wudang-zhang");

	prepare_skill("unarmed", "taiji-quan");
	prepare_skill("strike", "wudang-zhang");

	create_family("�䵱��", 2, "����");

	set("inquiry", ([
		"��צ������": (: ask_me :),
		"����": (: ask_me :),
		"����"  : (: ask_me :),
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.lian" :),
		(: perform_action, "sword.sui" :),
		(: perform_action, "unarmed.zhen" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}) );

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 150);
	set_temp("apply/unarmed_damage", 150);

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query("shen") < 15000 )
	{
		command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
			"�Ƿ����ò�����");
		return;
	}

	if ((int)ob->query_skill("wudang-xinfa",1) < 80)
	{
		command("say ���䵱����ע���ڹ��ķ�" + RANK_D->query_respect(ob)+
			"�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��?");
		return;
	}

	if ((int)ob->query_skill("taoism", 1) < 80)
	{
		command("say ϰ����Ϊ��ǿ���壬һζ�������ǲ���ȡ�ġ�");
		command("say �ҿ��㻹��Ҫ���������Է������������������"
			"��ĵ����ķ���");
		return;
	}

	command("say �ðɣ��Ҿ��������ˡ�");
	command("say ϣ�����ܺú��ù����������䵱����");
	command("recruit " + ob->query("id"));
	if( (string)ob->query("class") != "taoist")
		ob->set("class", "taoist");
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/huzhua-shou/juehu"))
		return "��һ���㲻���Ѿ�������";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

	if (me->query("shen") < 100000)
		return "��һ��̫�����ޣ����������ȥ�ҿ��²����ģ�";

	if (me->query_skill("huzhua-shou", 1) < 120)
		return "��Ļ�צ�����ֻ������ң������Լ�����ȥ�����ϰ�ɡ�";

	message_vision(HIY "$n" HIY "̾�˿�������$N" HIY
		       HIY "��������˵�˼��仢צ�����ֵľ�Ҫ��"
		       "�������ã���̾��һ������"NOR"\n",
		       me, this_object());
	command("sigh");
	command("say ����ǻ�צ�����ֵľ�Ҫ���ڣ������м�ʹ��֮ǰһ��Ҫ���ؿ��ǡ�");
	tell_object(me, HIC "��ѧ���ˡ���������һ�С�"NOR"\n");
	if (me->can_improve_skill("claw"))
		me->improve_skill("claw", 160000);
	me->set("can_perform/huzhua-shou/juehu", 1);
	return 1;
}
