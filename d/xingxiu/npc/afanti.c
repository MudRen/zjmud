// npc: /d/xingxiu/npc/afanti.c
#include <ansi.h>

inherit NPC;

void create()
{
	set_name("������", ({ "afanti" }) );
	set("gender", "����" );
	set("age", 48);
	set("long", 
	    "��ͷ�ϰ���ͷ�����������̵İ��ֺ�����ϲ��׽Ū�������������ˡ����������˳����\n");
	set("str", 25);
	set("dex", 20);
	set("con", 17);
	set("int", 15);
	set("shen_type", 1);

	set_skill("unarmed", 30);
	set_skill("dodge", 25);
	set_temp("apply/attack", 25);
	set_temp("apply/defense", 25);
	set("combat_exp", 2500);

	set("attitude", "peaceful");
	set("inquiry", ([
	    "name" : "�Ҿ������ն��İ����ᡣ",
	    "���ն�" : "���ҳ����ĵط���",
	    "����" : "�����ҹ�������г��кȣ��ҾͲ����ˡ������Ǹ�������Ը����ͷ�����",
	    "Сë¿" : "�ҵ�Сë¿���ҵ�ɳĮ��ƭ�����ֽ���ʱ�߶��ˡ�",
	    "����" : "������������������������",
	    "����" : "�����������������Ψ���������º�Ĭ����������ʹ�ߡ�",
       ]) );

	setup();
	set("chat_chance", 10);
	set("chat_msg", ({
	     "������̾�˿������ˣ���ϧ�ҵ�¿��\n",
	}) );
	carry_object("/clone/cloth/wcloth")->wear();
	carry_object("/d/xingxiu/obj/dongbula");
}

int accept_object(object who, object ob)
{
     	if ((string)ob->query("id") != "mao lv")
		return 0;

	write("������Ц���춼�ϲ����ˣ�˵����л��λ" + RANK_D->query_respect(who) + "�İ�����\n");

	if (who->query("score") < 100)
	{
		who->add("score", 5 + random(5));
		tell_object(who, HIG "��Ľ�����������ˡ�"NOR"\n");
	}

	destruct(ob);
	return 1;
}

