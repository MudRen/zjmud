// su.c ����

#include "shenlong.h"

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;

mixed ask_skill();

void create()
{
	set_name("����", ({ "su quan", "su" }));
	set("title",  HIY"������"NOR"��������" );
	set("long", "�����������̽����鰲ͨ�ķ��ˡ�\n");
	set("gender", "Ů��");
	set("age", 23);
	set("attitude", "friendly");
	set("str", 35);
	set("int", 30);
	set("con", 30);
	set("dex", 38);
	
	set("max_qi", 3500);
	set("max_jing", 1800);
	set("neili", 3700);
	set("max_neili", 3700);
	set("jiali", 50);
	set("combat_exp", 620000);
	set("shen_type", -1);

	set_skill("force", 150);
	set_skill("shenlong-xinfa", 150);
	set_skill("dodge", 180);
	set_skill("yixingbu", 160);
	set_skill("hand", 150);
	set_skill("strike", 180);
	set_skill("shenlong-bashi", 150);
	set_skill("huagu-mianzhang", 120);
	set_skill("parry", 150);
	set_skill("staff", 150);
	set_skill("shedao-qigong", 120);
	set_skill("literate", 100);
	set_skill("medical", 200);
	set_skill("shenlong-mixin", 200);

	map_skill("force", "shenlong-xinfa");
	map_skill("dodge", "yixingbu");
	map_skill("strike", "huagu-mianzhang");
	map_skill("hand", "shenlong-bashi");
	map_skill("parry", "shedao-qigong");
	map_skill("staff", "shedao-qigong");
	prepare_skill("strike", "huagu-mianzhang");
	prepare_skill("hand", "shenlong-bashi");

	create_family("������", 1, "��������");

	set("inquiry", ([
		"������" : "һ�������벻���������̵�(join shenlongjiao)��",
		"���"   : "һ�������벻���������̵�(join shenlongjiao)��",
		"�˽�"   : "�����������˽̣���ô�����һ����������𣬲��������Ѿ������ˡ�",
		"�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��",
		"rujiao" : "һ�������벻���������̵�(join shenlongjiao)��",
		"tuijiao": "�����������˽̣���ô�����һ����������𣬲��������Ѿ������ˡ�",
		"����"    : (: ask_skill :),
		"�������": (: ask_skill :),
	]));

	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: command("smile") :),
		(: command("haha") :),
		(: command("chat ƾ����" + RANK_D->query_rude(this_player())+",Ҳ����̫��үͷ�϶���?\n") :),
		(: command("say ���ò��ͷ�����������\n") :),
		(: perform_action, "staff.chang" :),
		(: perform_action, "staff.chang" :),
		(: perform_action, "staff.chang" :),
		(: perform_action, "staff.chang2" :),
		(: perform_action, "staff.chang2" :),
		(: perform_action, "staff.chang2" :),
		(: perform_action, "staff.chang3" :),
		(: perform_action, "staff.chang3" :),
		(: perform_action, "staff.chang3" :),
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
	}) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 50);
}

void init()
{
	object ob;

	::init();

	if (interactive(ob = this_player()) && ! is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
	add_action("do_join", "join");
}

void greeting(object ob)
{
	object obj;
	if (! objectp(ob)) return;
	if (interactive(ob) && objectp(obj = present("used gao", ob)))
	{
	   	set("combat_exp", 100000);
	   	set("qi", 100);
	   	set("jing", 100);
	}
}

void attempt_apprentice(object ob)
{
	command("say �ðɣ���ͺ���ѧ�书�ɡ�");
	command("recruit " + ob->query("id"));
}

mixed ask_skill()
{
	object me;

	me = this_player();

	if (me->query("can_perform/shenlong-bashi/huixiang"))
		return "�㲻���Ѿ�������";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "�������������̵��ˣ��γ����ԣ�";

	if (me->query_skill("shenlong-bashi", 1) < 160)
		return "���������ʽ�������ң�Ҫ��������";

	message_vision(HIY "$n" HIY "���˵�ͷ����$N" HIY
		       HIY "���������ֹ��˼��䣬������"
		       "���ȣ��ڿ��бȻ���һ�£�ͻȻ��"
		       "�͵���ǰ������\n��ʽ����������"
		       "$N" HIY "�������"NOR"\n",
		       me, this_object());
	command("nod");
	command("say ��������ˣ�");
	tell_object(me, HIC "��ѧ���ˡ�������衹��һ�С�"NOR"\n");
	if (me->can_improve_skill("hand"))
		me->improve_skill("hand", 160000);
	me->set("can_perform/shenlong-bashi/huixiang", 1);
	return 1;
}

