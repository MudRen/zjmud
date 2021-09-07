// ding.c ������

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

#include "xingxiu.h"

string ask_me();
string ask_du1();
string ask_du2();
string ask_xiangliao();
mixed  ask_duo();

void create()
{
	set_name("������", ({ "ding chunqiu", "ding" }));
	set("nickname", "�����Ϲ�");
	set("long", @LONG
�����������ɿ�ɽ��ʦ����������ʿ���ʹ���������Ϲֶ����
��������������ò���棬�ɷ���ǡ�
LONG );
	set("gender", "����");
	set("age", 60);
	set("attitude", "friendly");
	set("class", "scholar");
	set("shen_type", -1);
	set("str", 25);
	set("int", 30);
	set("con", 28);
	set("dex", 28);
	
	set("max_qi", 5400);
	set("max_jing", 2700);
	set("neili", 6300);
	set("max_neili", 6300);
	set("jiali", 100);
	set("combat_exp", 1850000);

	set_skill("force", 220);
	set_skill("huagong-dafa", 220);
	set_skill("guixi-gong", 200);
	set_skill("throwing", 210);
	set_skill("feixing-shu", 210);
	set_skill("dodge", 180);
	set_skill("zhaixinggong", 180);
	set_skill("strike", 185);
	set_skill("chousui-zhang", 185);
	set_skill("claw", 180);
	set_skill("sanyin-wugongzhao", 180);
	set_skill("whip", 180);
	set_skill("chanhun-suo", 180);
	set_skill("parry", 185);
	set_skill("staff", 190);
	set_skill("poison", 255);
	set_skill("tianshan-zhang", 190);
	set_skill("literate", 120);
	set_skill("medical", 265);
	set_skill("xingxiu-qishu", 265);

	map_skill("force", "huagong-dafa");
	map_skill("dodge", "zhaixinggong");
	map_skill("strike", "chousui-zhang");
	map_skill("claw", "sanyin-wugongzhao");
	map_skill("whip", "chanhun-suo");
	map_skill("parry", "tianshan-zhang");
	map_skill("staff", "tianshan-zhang");

	prepare_skill("strike", "chousui-zhang");
	prepare_skill("claw", "sanyin-wugongzhao");

	set("book_count", 1);
	set("zhen_count", 1);
	set("san_count", 1);
	set("xiangliao_count", random(10) + 5);

	set("inquiry", ([
		"����"     : (: ask_me :),
		"���޶���" : (: ask_me :),
		"������"   : (: ask_du1 :),
		"����"     : (: ask_xiangliao :),
		"���"     : (: ask_duo :),
		"������" : (: ask_duo :),
		"����"     : (: ask_duo :),
		"��Ц��ңɢ" : (: ask_du2 :),
		"��ң��Цɢ" : (: ask_du2 :),
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "staff.fugu" :),
		(: perform_action, "staff.xue" :),
		(: perform_action, "strike.biyan" :),
		(: perform_action, "strike.huolang" :),
		(: perform_action, "strike.huoqiu" :),
		(: perform_action, "strike.huoyan" :),
		(: perform_action, "claw.zhua" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	create_family("������", 1, "��ɽ��ʦ");
	set("class", "taoist");

	set_temp("apply/damage", 180);
	set_temp("apply/armor", 400);
	set_temp("apply/attack", 250);
	set_temp("apply/dodge", 250);
	set_temp("apply/parry", 250);

	setup();
	carry_object("/clone/weapon/gangzhang")->wield();
}

void init()
{
	object me;

	me = this_player();

	if (! interactive(me))
		return;

	if (living(this_object()) && present("shenmu wangding", me))
	{
		command("say �üһԭ����͵���ҵ���ľ�����������ɣ�");
		kill_ob(me);
		return;
	}

	add_action("do_flatter", "flatter");
}

void attempt_apprentice(object me)
{
	if ((int)me->query("shen") > -1000)
	{
		command("say ������Խ����Խ��׵������Ե׵ġ�");
		return;
	}

	if ((int)me->query("combat_exp") < 100000)
	{
		command("say �����΢ĩ���������ѧ�����ɵ������");
		return;
	}

	if ((int)me->query_skill("poison", 1) < 100)
	{
		command("say �㶾����ûѧ���ף������������ң�");
		return;
	}

	if( me->query_temp("pending/flatter"))
	{
		command("say ����˲������ɷ�����������������㣿");
		return;
	} else
	{
		command("say ���������ɱ������������ʥ����ô������");
		message_vision("�����Ϲ�΢��˫�ۣ������룬һ����������(flatter)�����ӡ�\n",
		this_player());
		me->set_temp("pending/flatter", 1);
	}
}

int do_flatter(string arg)
{
	if (! this_player()->query_temp("pending/flatter"))
		return 0;

	if (! arg) return notify_fail("��˵����ʲô��\n");
	this_player()->set_temp("pending/flatter", 0);
	message_vision("$N����˵����" + arg + "\n", this_player());
	if( strsrch(arg, "��������") >=0 && (strsrch(arg, "�������") >=0
	 || strsrch(arg, "�������") >=0 || strsrch(arg, "�Ž��ޱ�") >=0 )) {
		command("smile");
		command("say �⻹��ࡣ\n");
		welcome(this_player());
		command("recruit " + this_player()->query("id"));
	} else
	{
		command("say ����˲����ҷ���������������㣿");
	}
	return 1;
}

// �������ɣ�������أ��������Ž��ޱ�
string ask_me()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	if (query("book_count") < 1)
		return "�������ˣ����ɵ��ڹ��ķ����ڴ˴���";
	add("book_count", -1);
	ob = new("/clone/book/dujing_2");
	ob->move(this_player());
	return "�ðɣ��Ȿ�����޶��������û�ȥ�ú����С�";
}

string ask_du1()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	if (this_player()->query_skill("poison", 1) < 50)
		return "��Ķ������δ�����ò������ֶ�����";
	if (query("zhen_count") < 1)
		return "�������ˣ������붼�����ˡ�";
	add("zhen_count", -1);
	ob = new("/d/xingxiu/obj/bilinzhen");
	ob->move(this_player());
	return "�ðɣ������������Щ��ɡ�";
}

string ask_du2()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	if (this_player()->query_skill("poison", 1)<100)
		return "��Ķ������δ�����ò������ֶ�����";
	if (query("san_count") < 1)
		return "�������ˣ�����ûʲôʣ���ˡ�";
	add("san_count", -1);
	ob = new("/d/xingxiu/obj/sanxiaosan");
	ob->move(this_player());
	return "�ðɣ������ҩ���û�ȥ�Ƽ����ðɡ�";
}

string ask_xiangliao()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	if (is_busy() || is_fighting())
		return "�Ȼ����û��������æ����ô��";
	if (this_player()->query_skill("poison", 1) < 40)
		return "��Ķ������̫�����������˵�ɣ�";
	if (query("xiangliao_count") < 1)
		return "�������ˣ�����ûʲôʣ�µ������ˣ��㻹��ȥ�ֿ����ҿ��ɣ�";
	add("xiangliao_count", -1);
	ob = new("/clone/misc/xiangliao");
	ob->set_amount(random(50) + 100);
	ob->move(this_player());
	start_busy(2);
	return "�ðɣ���Щ��������ȥ�����ðɡ�";
}

void reset()
{
	set("xiangliao_count", random(10) + 5);
}

void unconcious()
{
	die();
}

mixed ask_duo()
{
	object me;
	int n;
	string msg;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
		return "���������ң�������";

	if (me->query("can_perform/chanhun-suo/duo"))
		return "��������ȥ����ȥ����Ҫ��������������ô�������ǵġ�";

	if (me->query_skill("chanhun-suo", 1) < 100)
		return "��Ѳ��������úø������ã���������Ҷ�����";

	message_sort("$N���ͷ����$n������Ҫ�뷢�����յ�����ٺ٣����"
		     "�����˿��͵�˿������˵�գ�$N�ͳ�һ��ϸϸ�ĳ�˿��"
		     "�ֵ����������ˣ����еİ����ȫ����������ˣ���"
		     "����㡣��$nƴ����ͷ����Ц������ʦ�����ǹ���������"
		     "�µ�һ�����ж��ǳ��������\n", this_object(), me);
	me->set("can_perform/chanhun-suo/duo", 1);
	tell_object(me, HIG "��ͨ���˶������İ��"NOR"\n");
	if (me->can_improve_skill("whip"))
		me->improve_skill("whip", 90000);
	return 1;
}
