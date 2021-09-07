// kanggl.c
// shilling 97.2

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xiaoyao.h"

string ask_me();

void create()
{
	set_name("������", ({ "kang guangling", "kang" }));
	set("long", 
		"ֻ�����߶�͹򪣬��ò��ţ�Ц���е���ɫ\n"
		"��Ϊ���ӣ����б���һ�����١�\n");
	set("gender", "����");
	set("age", 50);
	set("attitude", "friendly");
	set("class", "scholar");
	set("shen_type", 1);
	set("str", 28);
	set("int", 28);
	set("con", 28);
	set("dex", 38);

	set("inquiry", ([
		"����":(:ask_me:),
	]) );
	
	set("max_qi", 2200);
	set("max_jing", 1100);
	set("neili", 2400);
	set("max_neili", 2400);
	set("jiali", 40);
	set("combat_exp", 180000);

	set_skill("blade",100);
	set_skill("ruyi-dao",100);
	set_skill("force", 100);
	set_skill("dodge", 100);
	set_skill("strike", 100);
	set_skill("parry", 100);
	set_skill("feiyan-zoubi", 100);
	set_skill("xiaoyao-xinfa",100);
	set_skill("liuyang-zhang", 100);

	map_skill("strike", "liuyang-zhang");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("force", "xiaoyao-xinfa");
	map_skill("blade", "ruyi-dao");

	prepare_skill("strike", "liuyang-zhang");

	set("book_count", 1);

	create_family("��ң��", 3, "����");
	set("title","��ң�ɡ����Ȱ��ѡ�");
	set("nickname","�ٵ�");
	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/blade")->wield();

}

string ask_me()
{
	object me,ob;
	ob=this_player(); 
	if (query("book_count") < 1)
		return "�������ˣ��������Ѿ����͸������ˡ�";   

	add("book_count", -1);		  
	command("say �ðɣ����ҾͰ����͸����ˡ�\n");
	message_vision(HIY"������΢Ц�Ŵӻ����ó���һ���飬���˸�$N\n"NOR"\n",ob);
	me=new("/clone/book/hand_book");
	me->move(ob);
	return "�Ȿ���׿�ǧ��Ҫ�������ˡ�\n";
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query_int() < 25)
	{
		command("say ��̫����ʲô��ѧ���ᡣ");
		return;
	}

	command("say �ðɣ�������Ϊͽ����ѧЩ��������������������䡣");
	command("recruit " + ob->query("id"));
}
