 //dizi2.c ���� by river

#include <ansi.h>
inherit NPC;
int ask_xuexi2();

void create()
{
	set_name("����", ({ "zhou qi","zhou","qi", "man" }));
	set("title", "������ݶ�����");
	set("gender", "����");
	set("age", 32);         
	set("long", "��������ɽ�Ķ����ӣ���������������һ����ɹ����ڡ�\n");
	set("combat_exp", 8000);
	set("shen_type", 1);         

	set_skill("force", 60);
	set_skill("strike", 60);

	set("inquiry", ([
		"����ɽ" : "�����˼����ҵĶ�ʦ����",
		"ѧϰ" : (: ask_xuexi2 :),        
	]));

	setup();
}

void init()
{
	object ob;
	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if ( ob->query_temp("jobask") == 2){
		command("admire zhou");
		command("say ��λ" + RANK_D->query_respect(ob) +",����� "HIY HBCYN"ask zhou about ѧϰ"CYN" �������˽���������"NOR);
	}
}

int ask_xuexi2()
{      
	object ob = this_player();
	if(ob->query_temp("jobask") ==2 ) {      
	command("say ��λ" + RANK_D->query_respect(ob) +"Ҳ�Ǹյ������ɣ����ڽ����Ͽɻ��˺ü����ˣ���֪������\n"+
		"�����ô���ȿ����ҵ����ĵط� "HIY HBCYN"look tu"CYN" ��Ȼ�����Ҵ����� "HIY HBCYN"ask zhou about ***"CYN" ��"NOR);
		ob->delete_temp("jobask");
		if(ob->query_temp("jobover") != 2) {
			ob->set_temp("jobover", 2);
			command("say ��˵�����ֵܻ��е��������㣬�����ȥ��һ�¡�"NOR);
			if ( ob->query("combat_exp") < 200) {
				ob->add("potential", 20);
				ob->add("combat_exp",100);
				tell_object(ob,HIW"���������ߵĽ��⣬������һ�ٵ�ʵս����Ͷ�ʮ��Ǳ�ܣ��Խ����ֶ���һ���˽⡣"NOR"\n");
			}
		}
		return 1;
	}
	if ( ob->query_temp("jobover") == 2) {
		command("say �Ҳ��Ƕ�����˵��ô�������ֵ��������㣬��ȥ���°ɡ�");
		return 1;
	}
}
