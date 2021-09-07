#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

int ask_tuihui();
mixed ask_me();

void create()
{
	set_name("�½���", ({ "chen jinnan", "chen","jinnan" }));
	set("title", HIR "��ػ�"HIM"�ܶ���"NOR );
	set("nickname", HIC "Ӣ���޵�" NOR);
	set("long", 
		"\n����һ����ʿ����������������ɫ�Ͱ���\n"
		"������������������ػ��ܶ����½��ϣ�\n"
		"��˵ʮ�˰����գ�������ͨ��\n"
		"ż������߿��������پ���Ŀ����磬Ӣ�����ˡ�\n");
	set("gender", "����");
	set("class", "scholar");
	set("age", 45);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 5000);
	set("max_jing", 3000);
	set("neili", 5500);
	set("max_neili", 5500);
	set("jiali", 120);
	set("combat_exp", 2000000);
	set("score", 500000);

	set_skill("literate", 200);
	set_skill("force", 250);
	set_skill("dodge", 250);
	set_skill("unarmed", 250);
	set_skill("parry", 250);
	set_skill("claw", 250);
	set_skill("houquan", 250);
	set_skill("yunlong-xinfa", 250);
	set_skill("yunlong-shengong", 250);
	set_skill("yunlong-shenfa", 250);
	set_skill("ningxue-shenzhao", 250);

	map_skill("dodge", "yunlong-shenfa");
	map_skill("force", "yunlong-shengong");
	map_skill("unarmed", "houquan");
	map_skill("parry", "ningxue-shenzhao");
	map_skill("claw", "ningxue-shenzhao");

	prepare_skill("claw","ningxue-shenzhao");

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "claw.ji" :),
		(: exert_function, "recover" :),
	}) );

	create_family("������", 1, "��ɽ��ʦ");
	set("book_count", 1);
	set("inquiry", ([
		"��ػ�" :  "ֻҪ��Ӣ�ۺú���������������ػ�(join tiandihui)��",
		"���" :  "�����������ػ�һͬ���帴����",
		"����" : (: ask_me :),
		"����" : (: ask_me :),
		"����" : (: ask_me :),
		"��Ѫ��צ" : (: ask_me :),
		"�˻�" : (: ask_tuihui :),
		"tuihui"   : (: ask_tuihui :),
	]) );

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
	carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_join","join");
}

int ask_tuihui()
{
	object ob;

	ob = this_player();
	if (ob->query("party/party_name") != "��ػ�")
	{
		message_vision("�½���Ц��Ц����$N˵�����㻹û"
			       "��������ػ��أ���ʲô�ˣ�\n", ob);
		return 1;
	}
	command("look "+ob->query("id"));
	command("sigh ");
	command("say ���帴������Ҫ����־ʿ����ȥ��! ");
	ob->delete("party");
	ob->delete("rank");
	ob->delete("level_tdh");
	return 1;
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/ningxue-shenzhao/ji"))
		return "����Ὺ��Ц�����˻������ҡ�";

	if (! me->query("story/shenzhao"))
		return "�����������";

	if (me->query("shen") < 300000)
		return "ϰ��֮������һ���������֣����巽���㻹���ò�����";

	if (me->query_skill("ningxue-shenzhao", 1) < 250)
		return "�����Ѫ��צ�������ң�Ҫ��������";

	message_vision(HIY "$n" HIY "���˵�ͷ������Ϊצ��"
		       "�������������˫צ��ʱ�ó�����צӰ��"
		       "���ƻֺ��ޱȡ�"NOR"\n",
		       me, this_object());
	command("nod");
	command("say ��������ˣ�");
	tell_object(me, HIC "��ѧ���ˡ����硹��һ�С�"NOR"\n");
	if (me->can_improve_skill("claw"))
		me->improve_skill("claw", 250000);
	if (me->can_improve_skill("ningxue-shenzhao"))
		me->improve_skill("ningxue-shenzhao", 250000);
	me->set("can_perform/ningxue-shenzhao/ji", 1);
	return 1;
}

void unconcious()
{
	die();
}

#include "/kungfu/class/yunlong/tiandihui.h"

