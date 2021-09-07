// feng-buping.c  �ⲻƽ

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include <ansi.h>
#include "jianzong.h"

mixed ask_feilong();
mixed ask_sanxian();
mixed ask_sword_martial();

void create()
{
	set_name("�ⲻƽ", ({ "feng buping", "feng" }) );
	set("nickname", YEL"���콣"NOR);
	set("gender", "����");
	set("class", "swordsman");
	set("title", "��ɽ���ڵ�ʮ��������");
	set("age", 45);
	set("long",
		"�ⲻƽ�ǻ�ɽ���ڵ�һ���֣���������һ�Żƽ�������Ƥ��\n");
	set("attitude", "peaceful");
	set("str", 28);
	set("int", 32);
	set("con", 31);
	set("dex", 29);

	set("max_qi", 4700);
	set("max_jing", 2400);
	set("neili", 5000);
	set("max_neili", 5000);
	set("jiali", 50);

	set("combat_exp", 1800000);
	set("shen_type", -1);
	set("apprentice_available", 3);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "sword.feilong" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}) );

	set_skill("unarmed", 180);
	set_skill("sword", 220);
	set_skill("force", 200);
	set_skill("parry", 200);
	set_skill("strike", 180);
	set_skill("dodge", 190);
	set_skill("literate", 100);
	set_skill("huashan-sword", 220);
	set_skill("kuangfeng-jian", 220);
	set_skill("huashan-xinfa", 200);
	set_skill("huashan-quanfa", 180);
	set_skill("huashan-zhangfa", 180);
	set_skill("huashan-shenfa", 190);

	map_skill("sword", "kuangfeng-jian");
	map_skill("parry", "kuangfeng-jian");
	map_skill("force", "huashan-xinfa");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("strike", "huashan-zhangfa");
	map_skill("dodge", "huashan-shenfa");

	set("inquiry", ([
		"����"   : "�ҽ��ڽ������棬����ѧ���ž��У�",
		"����"   : "�ҽ��ڽ������棬����ѧ���ž��У�",
		"��������" : (: ask_sword_martial :),
		"�������" : (: ask_feilong :),
		"�����������ɽ�" : (: ask_sanxian :),
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.kuang" :),
		(: exert_function, "recover" :),
	}) );

	set_temp("apply/attack", 220);
	set_temp("apply/defense", 220);
	set_temp("apply/damage", 200);
	set_temp("apply/unarmed_damage", 200);

	create_family("��ɽ����", 13, "����");

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

mixed ask_feilong()
{
	object me;

	me = this_player();
	if (me->query("can_perform/huashan-sword/feilong"))
		return "�㻹����ȥ��ϰ�书��һѩ���ǽ����߳ܣ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "�������ǻ�ɽ���ڵ��ˣ����߰ɣ�";

	if (me->query_skill("huashan-sword", 1) < 150)
		return "��Ļ�ɽ�����������ң���Ҫ�ٸ��Ҷ����ˣ�";

	message_vision(HIY "$n" HIY "���һ��������ճ��һ��ʯ��"
		       "�����������������ͻȻ������ĩ��\n"
		       HIY "$n" HIY "��ͷ������$N" HIY "������һ"
		       "��ûʲôϡ�棬����Ҫ��������������������"
		       "����Ϊ���ڵ��ӣ�ҲҪ�ú�����������"NOR"\n",
		       me, this_object());
	tell_object(me, HIG "��ѧ�������������"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 90000);
	me->set("can_perform/huashan-sword/feilong", 1);
	return 1;
}

mixed ask_sanxian()
{
	object me;

	me = this_player();
	if (me->query("can_perform/huashan-sword/sanxian"))
		return "�㻹����ȥ��ϰ�书��һѩ���ǽ����߳ܣ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "�������ǻ�ɽ���ڵ��ˣ����߰ɣ�";

	if (me->query_skill("huashan-sword", 1) < 135)
		return "��Ļ�ɽ����ѧ��������ӣ������������ֽ̾�����";

	message_vision(HIY "$n" HIY "���˿����ܣ��������ˣ�����վ�������������ݳ���������ʽ\n"
		       "��������Ƿ�����˼��\n"
		       HIY "$n" HIY "���£���˼���ã��˵��������꽣���������ҽ��ڵ���ʹ����\n"
		       "�ž��������жԷ��������֣�������ͬС�ɡ����Ҫ�ú���ϰ��"NOR"\n",
		       me, this_object());
	tell_object(me, HIG "��ѧ���˶����������ɽ���"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 90000);
	me->set("can_perform/huashan-sword/sanxian", 1);
	return 1;
}

mixed ask_sword_martial()
{
	object ob;
	object me;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) +
		       "�������������Լ�Ҫ�ڼ���������";

	if (me->query("combat_exp") < 200000)
		return "������书Ҳ��������̽�������úø�������ȥ��";

	if (me->query_skill("sword-cognize", 1) < 10)
		return "����޽����������������������̸���а��";

	if (me->query_skill("sword-cognize", 1) >= 200)
		return "�㽣���˽���Ѿ������ˣ�����ûʲô���ٽ�����ˡ�";

	if (me->query_temp("last_ask/murongbo/martial") + 60 > time())
		return "������̸�ɣ�������Ҫ�����룬�ú������ᡣ";

	message_vision("$N����$n���������ðɣ��Ҿ�����̸̸���ڽ���������ĵá���\n",
		       this_object(), me);

	if (me->query("potential") - me->query("learned_points") < 100)
	{
		tell_object(me, "���������Ժ����ģ�û����������Ȼ��������Ǳ�ܲ�����\n");
		return 1;
	}

	me->add("learned_points", 100);
	tell_object(me, HIG "���������л�Ȼ���ʣ�ͨ���˲��ٽ����İ��"NOR"\n");
	me->set_temp("last_ask/murongbo/martial", time());
	me->improve_skill("sword-cognize", 1500 + random(2000));
	return 1;
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob) )
		return;

	if (query("apprentice_available"))
	{
		if (find_call_out("do_recruit") != -1)
			command("say ������һ��һ������");
		else
			call_out("do_recruit", 2, ob);
	} else
	{
		command("say �Ϸ�����Ѿ������������ӣ���������ͽ�ˡ�");
	}
}

void do_recruit(object ob)
{
	if ((int)ob->query_int() < 24)
		command("say �һ�ɽ���Խ���Ϊ�������ҿ�" + RANK_D->query_respect(ob) +
			"���������ʺ���ѧ������");
	else
	{
		command("say �ã��ã��ã��ܺá�");
		command("recruit " + ob->query("id"));
	}
}

int recruit_apprentice(object ob)
{
	if (::recruit_apprentice(ob))
		ob->set("title", "��ɽ���ڵ�ʮ�Ĵ�����");
		add("apprentice_availavble", -1);
}

void reset()
{
	set("apprentice_available", 3);
}
