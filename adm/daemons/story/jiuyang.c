// story:jiuyang ������

#include <ansi.h>

static string char_id;
static string char_name;

int give_gift();
object select_character();

static mixed *story = ({
	"һ�ѷ𾭡�",
	"$N����һ��ϸϸ�Ŀ��˰��죬ȴ����Ҫ�죬���������һ���𾭣�û�а���书���ϡ�",
	"$N��˼Ƭ�̣����鷴�˹��������������ֶ�������û��ʲô���",
	"ʢŭ֮�£�$N�����������˿�ȥ���ּ���һ����ȴ�ǡ���վ�����",
	"�ж�Ƭ�̣�����һ�ѷϻ���",
	"�����д��������µĲؾ���ͷ�����Щ��������$N���а�������Ī������ɮ����ʵ�������书����",
	"����涪�������Ѿ����˼�ʮ�����飬û���ҵ����ͷ����",
	"$N���ɵð����п࣬���˿��������ŵĻ���͵�һ���ˣ����룺��δ����ؾ���ʵ���Ǹ�ð���գ���Ȼ...",
	"һʱ��$N���ɵ���ͷ��ŭ�������еľ���˺�˸����飬��ʱֽƬ���",
	"��Ȼ������ֽƬƮ��$N����ǰ���ƺ�д�ţ������˽裬���ɼ������������ɼ���...",
	"$N��ʶ�����������⼸�����е�ʱһ����������Ǽ��ϳ˵���ѧ���ϣ�",
	"$N���˿�����ʣ�µİ���飬��Ȼ��һ��������٤������ֻ���з������������д��һЩ���֡�",
	"ֻ�Ǿ����Ѿ�ȱ��һ�룬����Ǻã�$N��æ�ڵ�������Ѱ�ң�����ֽһƬƬѰ�ء�",
	"������ƬϤ���Ѻã���Ȼ��������ʱ����$Nϸϸ������ԭ���⡶��٤�����з��о�Ȼ¼��һ�ݾ����澭��",
	"$N���°�����ĥ�����껪ɽ�۽���Ҳ����������һ�������澭���ѣ������ҵ��˴��飬������������",
	"$N�漴����̨�ý���������Ħ�澭Ҫּ��ֻ���澭�����һʱδ��ȫȻ����",
	"�ۼ���ɫ����$N���Ҿ����������飬�����룬�ְѾ��Ŀ�ͷһ�γ���˺�飬����պá�",
	"$N���������һ�ȥϸϸ�ж�������澭�����������޵У������գ�",
	"��գ�$NԾ����ȥ����ȻƮʧ��ҹĻ�С�",
	(: give_gift :),
});

void create()
{
	seteuid(getuid());

	if (! objectp(select_character()))
	{
		STORY_D->remove_story("jiuyang");
		destruct(this_object());
		return;
	}
}

string prompt() { return HIG "������������" NOR; }

object select_character()
{
	object *obs;
	object ob;

      obs = filter_array(all_interactive(),
               (: living($1) && 
			      $1->query_skill("jiuyang-shengong", 1) < 1 &&
			      $1->query("combat_exp") >= 100000 &&
			      $1->query("combat_exp") < 1500000 &&
			      SKILL_D("jiuyang-shengong")->valid_learn($1) &&
			      ! wizardp($1) &&
			      ! $1->query("story/jiuyang") &&
                  $1->query("jiuyangid") :));

	if (sizeof(obs) < 1) {
	    obs = filter_array(all_interactive(),
			   (: living($1) &&
			      $1->query_skill("jiuyang-shengong", 1) < 1 &&
			      $1->query("combat_exp") >= 100000 &&
			      $1->query("combat_exp") < 1500000 &&
			      SKILL_D("jiuyang-shengong")->valid_learn($1) &&
			      ! wizardp($1) &&
			      ! $1->query("story/jiuyang") :));
	    if (! sizeof(obs))
		return 0;

	    ob = obs[random(sizeof(obs))];

	} else
		if (!ob = obs[0]) return 0;

	char_id = ob->query("id");
	char_name = ob->name(1);
    ob->delete("jiuyangid");
	return ob;
}

mixed query_story_message(int step)
{
	mixed msg;

	if (step >= sizeof(story))
		return 0;

	msg = story[step];
	if (stringp(msg))
	{
		msg = replace_string(msg, "$N", char_name);
		msg = replace_string(msg, "$ID", char_id);
	}
	return msg;
}

int give_gift()
{
	object ob;
	object book;

	ob = find_player(char_id);
	if (! ob) return 1;

	if (ob->query_skill("jiuyang-shengong", 1) < 50)
		ob->set_skill("jiuyang-shengong", 50);

	ob->set("story/jiuyang", 1);
	tell_object(ob, HIC "��ѧϰ���˾����񹦡�"NOR"\n");
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵������"
			      "�ؾ���ʧ�ԣ���ʧ��٤��һ����");
	log_file("story", sprintf("%s��%s(%s)�齱����ˡ������澭����\n",ctime(time()),ob->query("name"),ob->query("id")));
	book = new("/clone/book/jiuyang-book");
	book->move(ob, 1);
	STORY_D->remove_story("jiuyang");
	return 1;
}
