inherit F_MASTER;
inherit F_UNIQUE;
inherit NPC;

string ask_me(); 

#include <ansi.h>

void greeting(object ob);

void create()
{
    seteuid(getuid());
    set_name("һ�ƴ�ʦ", ({ "yideng dashi", "yideng", "dashi" }));
    set("long","һ�ƴ�ʦ�˽������˳ơ���а�������ϵ۱�ؤ���е��ϵ۶�"
		"��ү������ƾ�Ŷ��ϡ�һ��ָ�����������֣�������֡���"
		"ȴ������ʱ��һ�α��������Ϊɮ��֮��󳹴��򣬳�Ϊһ"
		"λ�õ���ɮ��");
    set("title",HIY "����λ�ү" NOR);
    set("nickname", HIY "�ϵ�" NOR);
    set("gender", "����");
    set("age", 71);
	set("no_get", 1);
    set("shen_type", 1);
    set("attitude", "friendly");

    set("str", 33);
    set("int", 35);
    set("con", 38);
    set("dex", 33);

    set("qi", 5800);
    set("max_qi", 5800);
    set("jing", 2700);
    set("max_jing", 2700);
    set("neili", 8000);
    set("max_neili", 8000);
    set("jiali", 120);

    set("combat_exp", 2900000);
    set("score", 455000);

    //����ѧϰ
    set_skill("force", 280);
    set_skill("dodge", 280);
    set_skill("parry", 280);
    set_skill("cuff", 280);
    set_skill("sword", 280);
    set_skill("staff", 280);
    set_skill("finger", 280);
    set_skill("duanshi-xinfa", 280);
    set_skill("tiannan-step", 280);
    set_skill("jinyu-quan", 280);
    set_skill("duanjia-sword", 280);

    //�μҿ���ѧϰ
    set_skill("sun-finger", 280);

    //��������ѧϰ
    set_skill("literate", 200);
    set_skill("sanscrit", 200);
    set_skill("buddhism", 200);

    map_skill("force", "duanshi-xinfa");
    map_skill("dodge", "tiannan-step");
    map_skill("finger", "sun-finger");
    map_skill("cuff", "jinyu-quan");
    map_skill("strike", "wuluo-zhang");
    map_skill("parry", "sun-finger");
    map_skill("sword", "duanjia-sword");
    map_skill("staff", "duanjia-sword");

    prepare_skill("finger", "sun-finger");

    set("inquiry",([
	  "������" :     "����ͨ�������������������ĺ��������\n",
	  "����" :       "�������ĳ���ǰ��һ����Ե������Ҳ�ա�\n",
	  "����ͯ" :     "�Ǻǣ������书��ǿ�������Ļ�ȴ����ͯһ�㡣\n",
	  "����" :       "Ŷ���Ǹ���С���ĵ��������Һ���ʵ��û����һ��Ҫ�Կ���\n",
	  "����" :       "�ǹ����Ǻ�С�ӵİ��°ɣ��˵����ǻ��顣\n",
	  "����" :       "��ֻ�ܴ����� �����ķ� (buddhism)������д�� (literate)������ (sanscrit)����\n���������ʦ��ѧϰ�ɡ�\n",
	  "һ��ָ" : (: ask_me :),
    ]));

    setup();
    carry_object("/clone/cloth/seng-cloth")->wear();

	create_family("���ϻ���", 11, "����");

}

void greeting(object ob)
{
	if (! ob || environment(ob)!=environment()) return;
	if ((int)ob->query("shen") < -50000)
	{
		command("say ��λʩ�������������أ�Ȱʩ������Ϊ֪��");
	} else
	if ((int)ob->query("shen") < -5000)
	{
		command("say ��λʩ�����м�ħ������������");
	} else
	if((int)ob->query("shen") < -100)
	{
		command("say ��λʩ�������н��������е����������߽�аħ�����");
	} else
	if((int)ob->query("shen") >= 0)
	{
		command("say ��λʩ�����������������ߣ���ʩ����ӱ��ء�");
	} else
	if((int)ob->query("shen") > 50000)
	{
		command("say ��λʩ�����¹������䣬�ձ�Ϊ�����̳���");
	}
	return;
}

int accept_fight(object ob)
{
	if ((ob->query("combat_exp") < 50000))
	{
	message_vision("һ�ƴ�ʦ΢Ц������Ϊ" + RANK_D->query_respect(ob) +
		       "���㲻�����ĵĶ��֣�������ν֮����\n",ob);
	return 0;
	}
	message_vision("һ�ƴ�ʦ΢Ц������λ" + RANK_D->query_respect(ob) +
		       "����������ˡ�\n", ob);
	return 1;
}

string ask_me() 
{
	object me;

	me = this_player();

	if (me->query("shen") < 0)
		return "ʩ�������������أ�������֮�������Իᴫ�ڸ��㡣";

	if (me->query_skill("sun-finger", 1) > 280)
	       return "���һ��ָ���������־��磬������ûʲô�ɽ̵��ˡ�";

	if (me->query("family/family_name") != query("family/family_name"))
	       return "�����������ģ��㲻���Ҷμ�֮�ˣ���������֮�ֽ����ѧ�������������²��ס�";

	if (me->query("combat_exp") < 500000)
	       return "�书��ע�ظ�������Ḭ̄ͼ�ݾ�����ѻ��������ú������Իᴫ�ڸ��㡣";

	me->add_temp("can_learn_sun-finger/yideng", 1);
	       return "�ðɣ����ľʹ���һ��ָ�������㣬���м����н��������е�������Ҫ�߽�аħ�����"; 
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("shen") < 0)
	{
		command("say ʩ�������������أ�������֮�������Իᴫ�ڸ��㣡");
		return -1;
	}

	if (skill != "literate" && skill != "sanscrit" && skill != "buddhism" && skill != "sun-finger")
	{
		command("say ��Щ���������ʦ��ѧ�ɣ����ܴ���һЩ֪ʶ���㡣");
		return -1;
	}

	if (!me->query_temp("can_learn_sun-finger/yideng") && skill == "sun-finger")
	{
		command("say һ��ָ�Ҳ����״��ڡ�");
		return -1;
	}

	return 1;
}
