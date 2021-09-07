// lu.c
#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
string ask_me();

void create()
{
	set_name("½����", ({ "lu gaoxuan", "lu" ,"gaoxuan"}));
	set("title", HIY"������"NOR"��ʦ");
	set("nickname",HIC "�������" NOR);
	set("long", "����ͥ������������Բ����ò��ΪӢ����\nȻ��������ݣ�ǡ"
		    "����̼����ɱ��֮��һ�㡣\n");
	set("gender", "����");
	set("age", 37);

	set("str", 24);
	set("int", 35);
	set("con", 26);
	set("dex", 25);

	set("max_qi", 3500);
	set("qi", 3500);
	set("max_jing", 1800);
	set("jing", 1800);
	set("neili", 3300); 
	set("max_neili", 3300);
	set("jiali", 30);

	set("combat_exp", 360000);
	set("shen_type", -1);
	set("attitude", "peaceful");

	set_skill("force", 120);
	set_skill("shenlong-xinfa", 120);
	set_skill("dodge", 120);
	set_skill("yixingbu", 120);
	set_skill("hand", 120);
	set_skill("shenlong-bashi", 120);
	set_skill("parry", 120);
	set_skill("staff", 120);
	set_skill("shedao-qigong", 120);
	set_skill("literate", 120);

	map_skill("force", "shenlong-xinfa");
	map_skill("dodge", "yixingbu");
	map_skill("hand", "shenlong-bashi");
	map_skill("parry", "shedao-qigong");
	map_skill("staff", "shedao-qigong");
	prepare_skill("hand", "shenlong-bashi");

	create_family("������", 0, "��ɢ����");

	set_temp("apply/damage", 60);
	set("book_count", 1);

	set("inquiry", ([
		"������" : "һ�������벻���������̵�(join shenlongjiao).\n",
		"���"   : "һ�������벻���������̵�(join shenlongjiao).\n",
		"�鰲ͨ" : "����Ƣ������,Ҫ�������Ĳźá�\n",
		"����"   : "����Ƣ������,Ҫ�������Ĳźá�\n",
		"�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��",
		"�ؼ�"   : (: ask_me :),
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 10);
}

void init()
{
	object ob;

	if (interactive(ob = this_player()) && !is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
}

void greeting(object ob)
{
	object obj;
	if (! objectp(ob)) return;
	if (interactive(ob) && objectp(obj = present("used gao", ob)))
	{
	   	set("combat_exp", 1000000);
	   	set("qi", 1500);
	   	set("jing", 1500);
	}
}

void attempt_apprentice(object ob)
{
	command("sigh");
	command("say �Ϸ�æ�úܣ��ֲ���ͽ��");
}

string ask_me()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (query("book_count") < 1)
		return "�������ˣ����̵��ؼ����ڴ˴���";

	add("book_count", -1);

	if (random(2) == 0) ob = new("/clone/book/shoufa");
	else ob = new("/clone/book/bufa");

	ob->move(this_player());
	return "�ðɣ��Ȿ��"+ob->query("name")+"�����û�ȥ�ú����С�";
}

