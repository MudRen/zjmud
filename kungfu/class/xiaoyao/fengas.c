// shilling 97.2

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xiaoyao.h"

string ask_me();

void create()
{
	set_name("�밢��", ({ "feng asan", "feng" }));
	set("long", 
		"��˵������³��ĺ��ˣ������ĵ�һ�ɽ�����ƻ��ص����֡�\n");
	set("gender", "����");
	set("age", 40);
	set("attitude", "friendly");
	set("class", "alchemist");
	set("shen_type", 1);
	set("str", 38);
	set("int", 28);
	set("con", 30);
	set("dex", 28);

	set("inquiry", ([
		"����":(:ask_me:),
	]) );

	set("max_qi", 1500);
	set("max_jing", 700);
	set("neili", 1800);
	set("max_neili", 1800);
	set("jiali", 30);
	set("combat_exp", 60000);
	set("score", 20000);

	set_skill("blade",50);
	set_skill("ruyi-dao",50);
	set_skill("force", 50);
	set_skill("dodge", 50);
	set_skill("strike", 50);
	set_skill("parry", 50);
	set_skill("feiyan-zoubi", 50);
	set_skill("xiaoyao-xinfa",50);
	set_skill("liuyang-zhang", 50);

	map_skill("strike", "liuyang-zhang");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("force", "xiaoyao-xinfa");
	map_skill("blade", "ruyi-dao");

	prepare_skill("strike", "liuyang-zhang");

	create_family("��ң��", 3, "����");
	set("title","��ң�ɡ����Ȱ��ѡ�");
	set("nickname","�ɽ�");
	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/blade")->wield();

}

string ask_me()
{
	object me,ob;
	ob = this_player(); 

	if (random(100)<70)
		return "������ƻ��ط������е��س����ô�Ҽ�Ц�ˡ�";   
	command("laugh");
	return "�����ң����ڿ����ء�������֥�鿪�š��������������Ц\n";
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query_int() < 26)
	{
		command("say �������ԣ���... Ц�����ˡ�");
		return;
	}

	command("say �ðɣ��Ҿ��������ˣ���ɻ��˵����");
	command("recruit " + ob->query("id"));
}

