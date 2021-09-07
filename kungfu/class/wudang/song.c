#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_COAGENT;

string ask_me();
string ask_book();
mixed ask_skill();

void create()
{
	set_name("��Զ��", ({ "song yuanqiao", "song" }));
	set("nickname", "�䵱����");
	set("long", 
		"������������Ĵ���ӡ��䵱����֮�׵���Զ�š�\n"
		"��һ���ɸɾ����Ļ�ɫ���ۡ�\n"
		"������ݳ���������⡣�񵭳�ͣ���Ĭ���ԡ�\n");
	set("gender", "����");
	set("age", 61);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 31);
	set("int", 27);
	set("con", 32);
	set("dex", 30);
	
	set("max_qi", 5000);
	set("max_jing", 3000);
	set("neili", 7000);
	set("max_neili", 7000);
	set("jiali", 160);
	set("combat_exp", 1500000);
	set("score", 70000);

	set_skill("force", 200);
	set_skill("wudang-xinfa", 200);
	set_skill("taiji-shengong", 200);
	set_skill("dodge", 160);
	set_skill("tiyunzong", 160);
	set_skill("unarmed", 185);
	set_skill("taiji-quan", 185);
	set_skill("strike", 185);
	set_skill("wudang-zhang", 185);
	set_skill("zhenshan-zhang", 185);
	set_skill("hand", 185);
	set_skill("paiyun-shou", 185);
	set_skill("parry", 180);
	set_skill("sword", 185);
	set_skill("wudang-jian", 185);
	set_skill("shenmen-jian", 185);
	set_skill("taiji-jian", 185);
	set_skill("taoism", 190);
	set_skill("literate", 120);
	set_skill("medical", 200);
	set_skill("liandan-shu", 200);

	set("no_teach", ([
		"taiji-shengong" : "Ҫ��ѧϰ̫����������������̡�",
		"taiji-jian"     : "̫���������������״���",
		"taiji-quan"     : "̫��ȭ�����������״���",
	]));

	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-quan");
	map_skill("sword", "taiji-jian");
	map_skill("strike", "zhenshan-zhang");
	map_skill("hand", "paiyun-shou");

	prepare_skill("unarmed", "taiji-quan");
	prepare_skill("strike", "wudang-zhang");

	create_family("�䵱��", 2, "����");

	set("inquiry", ([
		"�ؼ�"     : (: ask_me :),
		"�䵱ҩ��" : (: ask_book :),
		"���Ŵ�"   : (: ask_skill :),
	]));

	set("book_count", 1);
	set("book2_count", 1);

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

	set("coagents", ({
		([ "startroom" : "/d/wudang/houyuan",
		   "id"	: "yu lianzhou" ]),
	}));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/greyrobe")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query("shen") < 25000)
	{
		command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
			"�Ƿ����ò�����");
		return;
	}

	if ((int)ob->query_skill("wudang-xinfa", 1) < 80)
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
	command("say ϣ������ȫ�����������ķ�������������裡");
	command("recruit " + ob->query("id"));
	if ((string)ob->query("class") != "taoist")
		ob->set("class", "taoist");
}

string ask_book()
{
	object ob;
	
	if (this_player()->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(this_player()) + 
		       "�뱾��������������֪�˻��Ӻ�̸��";

	if (this_player()->query_skill("liandan-shu", 1) < 60)
		return "����������ô�ҩ���ø���Ҳ��������";

	if (query("book2_count") < 1)
		return "�������ˣ��Ǳ��䵱ҩ���ڴ˴���";

	add("book2_count", -1);
	ob = new("/clone/book/wudang");
	ob->move(this_player(), 1);
	return "�ðɣ��Ȿ���䵱ҩ�������ȥ���ɡ�";
}

string ask_me()
{
	object ob;
	
	if (this_player()->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(this_player()) + 
		       "�뱾��������������֪�˻��Ӻ�̸��";

	if (query("book_count") < 1)
		return "�������ˣ����ɵ��ڹ��ķ����ڴ˴���";

	add("book_count", -1);
	ob = new("/clone/book/force_book");
	ob->move(this_player(), 1);
	return "�ðɣ��Ȿ��̫��ʮ��ʽ�����û�ȥ�ú����С�";
}

mixed ask_skill()
{
	object me;

	me = this_player();
	if (me->query("can_perform/shenmen-jian/ci"))
		return "�㲻���Ѿ�������";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

	if (me->query("shen") < 50000)
		return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

	if (me->query_skill("shenmen-jian", 1) < 120)
		return "�������ʮ�����������ң�Ҫ��������";

	message_vision(HIY "$n" HIY "���˵�ͷ����$N" HIY
		       HIY "���������ֹ��˼��䣬�ְγ�"
		       "���䳤�������������������Ȼ��"
		       "�͵�бб�̳���\n��ʽ���ӣ�����"
		       "��㻪�����ԡ�"NOR"\n",
		       me, this_object());
	command("nod");
	command("say ��������ˣ�");
	tell_object(me, HIC "��ѧ���ˡ����Ŵ̡���һ�С�"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 160000);
	me->set("can_perform/shenmen-jian/ci", 1);
	return 1;
}

