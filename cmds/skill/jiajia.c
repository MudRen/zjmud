// abandon.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int lvl;
	string skill;
	int queren;


	if (! arg || arg == ""||!me->query("exp301"))
		return notify_fail("������\n");

	if(sscanf(arg,"%s %d %d",skill,lvl,queren)==3)
	{
		if(lvl<1)
			return notify_fail("���ӵ�λ������Ҫ������ ������\n");
	}
	else if(sscanf(arg,"%s %d",skill,lvl)==2)
	{

	if (skill == "exp"&& lvl>0 && lvl<100000 && me->query("exp301")>lvl)
	  {
		tell_object(me,"���૵���߶�������飬�����飬��·���ɿ����飡"NOR"\n");
		//me->start_busy(1);
		me->add("exp301", -lvl);
		me->add("combat_exp", lvl);
	      log_file("static/jialian", sprintf("%s��%s("+me->query("id")+")����%d��%s��\n",ctime(time()),me->query("name"),lvl,skill ));
	      if (me->query("exp301")<1000) {
		  me->delete("exp301");
		  tell_object(me,HIR"������������ˣ�"NOR"\n");
              }
		return 1;
	  }
	return notify_fail("��������������Щ���Ծ�����\n");
   }

}

