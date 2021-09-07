// feng.c
#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;

int ask_me();

void create()								   
{
	set_name( "��Ĭ��" ,({ "feng mofeng", "feng" }));
	set("gender", "����");
	set("age", 39);
	set("long",
	    "��Ĭ���ǻ�ҩʦ��С��һ��ͽ�ܣ����ĸ������������ӽ�Ϊ��³��\n"
	    "���Ļ�������ʵ��һ���Һ���ʵ�����ӡ�\n");
	set("attitude", "friendly");
	set("class", "scholar");
	set("str", 30);
	set("int", 24);
	set("con", 27);
	set("dex", 23);
	set("shen_type",1);

	set("chat_chance", 1);
	set("chat_msg", ({
	    "��Ĭ��˵������ʦ���۰�Сʦ�ã�������⬼�һֱ��Сʦ�ô��š���\n",
	    "��Ĭ�����������˵����������һ����ˣ����򵥣���\n",
	}));

	set("max_qi", 4100);
	set("max_jing", 2100);
	set("neili", 4500);
	set("max_neili", 4500);
	set("jiali", 50);
	set("combat_exp", 950000);

	set_skill("force", 165);	    // �����ڹ�
	set_skill("luoying-xinfa", 165);    // ��Ӣ�ķ�
	set_skill("unarmed", 140);	  // ����ȭ��
	set_skill("xuanfeng-leg", 140);     // ����ɨҶ��
	set_skill("strike", 150);	   // �����Ʒ�
	set_skill("luoying-shenzhang", 150);// ��Ӣ����
	set_skill("dodge", 140);	    // ��������
	set_skill("anying-fuxiang", 140);   // ��Ӱ����
	set_skill("parry", 160);	    // �����м�
	set_skill("sword", 140);	    // ��������
	set_skill("luoying-shenjian", 140); // ��Ӣ��
	set_skill("literate", 90);	  // ����ʶ��

	map_skill("force"  , "luoying-xinfa");
	map_skill("unarmed", "xuanfeng-leg");
	map_skill("strike" , "luoying-zhang");
	map_skill("dodge"  , "anying-fuxiang");
	map_skill("parry"  , "luoying-shenjian");
	map_skill("sword"  , "luoying-shenjian");

	prepare_skill("unarmed", "xuanfeng-leg");
	prepare_skill("strike" , "luoying-zhang");

	create_family("�һ���", 2, "����");

	set("inquiry", ([
	   "�һ���":   "��������һ������������Ǳ��ɵ��ӣ�Ҫ���һ���",
	   "�һ���":   "���Ͼ����ˡ�",
	   "��а":     "��ʦ�˳ƶ�а���Ǻǡ�",
	   "����":     "ŷ���������ʦ���������ĸ��֣��˳��϶��",
	   "�ϵ�":     "����ʦ˵����ү���ڳ��ҵ��˺��У�����һ�ơ�",
	   "��ؤ":     "��ؤ���߹���ؤ��������������ݳ��⡣",
	   "����":     "����ʦ���İ�Ů��",
	   "��ҩʦ":   "��Ҫ�ݷü�ʦ��",
	   "��ʦ":     (: ask_me :),
	   "Ͷʦ":     (: ask_me :),
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian");
}									       

void attempt_apprentice(object ob)
{
	string master;
	if (! permit_recruit(ob))
		return;
	
	if (stringp(master = ob->query_temp("taohua/master")))
	{
		if (master != name())
		{
			command("say ��ʦ���������" + master +
				"��������ô���������ˣ�");
			return;
		}

		command("say �ðɣ���Ȼ��ʦ����Ҿ��������ˣ�����Ҫ�ú������һ����Ĺ�ء�");
		command("recruit " + ob->query("id"));
		ob->delete_temp("taohua/master");
		return;
	}

	if (ob->query("family/master_name") == "��ҩʦ" &&
	    ob->query("family/family_name") == "�һ���")
	{
		command("say ��Ҷ��ǻƵ����ĵ��ӣ���ͱ����Ѱ�����ˡ�");
		return;
	}

	command("shake");
	command("say �ҿɲ���������ͽ���㻹���Ҽ�ʦ�Ƶ����ɣ�");
}

int accept_fight(object ob)
{
	command("wield jian");
}

int ask_me()
{
	object me;

	me = this_player();
	if (me->query("family/family_name"))
	{
		if (me->query("family/family_name") != "�һ���")
		{
			command("say �����������ɣ���ʦ�ǲ���������ģ����߰ɣ�");
			return 1;
		}

		if (me->query("family/master_name"))
		{
			command("say �����������һ���ѧ�գ��ͱ���ҿ���Ц�ˡ�");
			return 1;
		}
	}

	if (me->query("detach/�һ���"))
	{
		command("say �������뿪���һ��������컹�һ�������ʦ��");
		return 1;
	}

	if (me->query("betrayer/times"))
	{
		command("say ������ʦ֮�ˣ���ʦ�Ǿ��Բ�������Ϊͽ�ģ�");
		return 1;
	}

	command("say �ðɣ��Ҵ�����һ������Լ�ȥ�һƵ����ɡ�");
	tell_object(me, "�㿪ʼ�ͽ�����Ĭ�硣\n");
	message_vision("$N�󲽵�������ȥ��$n�������\n", this_object(), me);
	this_object()->move("/d/taohua/damen");
	me->move("/d/taohua/damen");
	command("say ���ˣ��Ҵ��㵽���ţ����ȥ�Ϳ��Լ�����ʦ�ˣ��������ˡ�");
	message_vision("$NͷҲ���ص�������ȥ�ˡ�\n", this_object());
	this_object()->move(query("startroom"));
	message_vision("$N���Ҵҵ����˹�����\n", this_object());
	return 1;
}
