// feng.h 
// by Marz 

#include <ansi.h>

int look_feng(string arg);

int look_feng(string arg)
{
	int lucky;
	object me;

	if( !arg || arg!="feng" ) return 0;
	write("

		      ^
		     ^ ^
		   @@@__^    
		    ^ @@@__
		   ^   ^  ^

̧����ȥ������ƬƬ���������ƣ��������������֣���ң���ɼȡ�\n\n");

	me = this_player();
	lucky = random(me->query_dex() + me->query_kar()) + me->query_dex();

	if (lucky > 58)
	{
		write("ͻȻ�䣬�и��ڵ���������һ�Ӷ�����������һֻ���\n"
			+"������ô�ߵĵط�����ô�����أ���������Ҳ����һʱ�����ۡ�\n\n");
	
	}else if(lucky >= 45)
	{
		// do nothing here
	}else if(lucky >= 30)
	{
		message_vision(HIY"$N����ſ��죬һ���������̤�˸��գ�... ��...��\n"NOR"\n", me);
		message_vision(HIY"$Nһ������ˤ��һ�ӣ����ã�ֻ����ЩƤ�ǣ�û�й���ȥ��\n"NOR"\n", me);
		me->receive_damage("qi", 30+4*random((int)me->query("age")));
		me->receive_damage("jing", 50);
	}else // bad luck 
	{
		message_vision(HIR"$N�����̧ͷ���죬һ���������̤�˸��գ�... ��...��\n"NOR"\n", me);
		tell_object(me, HIR"����Ʋ�ס��ֱ��ɽ�¹���ֻ���û����޴����ۣ�ʹ��Ҫ������ȥ��\n"NOR"\n");
		me->move(__DIR__"tyroad8");
		message("vision", HIR"ֻ��" + me->query("name")
			+ "��ɽ�Ϲ�µµ�ع������������ڵ��ϰ�������������\n"NOR"\n",
			environment(me), me);
		me->unconcious();
	}
	
	return 1;
}
