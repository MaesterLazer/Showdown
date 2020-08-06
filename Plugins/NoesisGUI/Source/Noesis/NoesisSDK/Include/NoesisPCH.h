#ifndef __NOESIS_PCH_H__
#define __NOESIS_PCH_H__


// Core/Kernel
#include <NsCore/Type.h>
#include <NsCore/AssignableFromType.h>
#include <NsCore/Error.h>
#include <NsCore/Delegate.h>
#include <NsCore/TypeEnumImpl.h>
#include <NsCore/TypeEnum.h>
#include <NsCore/TypeClass.h>
#include <NsCore/Version.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/KernelApi.h>
#include <NsCore/TypeEnumHelper.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/BaseObject.h>
#include <NsCore/Symbol.h>
#include <NsCore/TypePropertyImpl.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/Boxing.h>
#include <NsCore/Find.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/StringUtils.h>
#include <NsCore/TypePropertyUtil.h>
#include <NsCore/BuildSettings.h>
#include <NsCore/TypeOf.h>
#include <NsCore/TypePointer.h>
#include <NsCore/Noesis.h>
#include <NsCore/MetaData.h>
#include <NsCore/PoolAllocator.h>
#include <NsCore/TypeProperty.h>
#include <NsCore/Interface.h>
#include <NsCore/Package.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/DynamicCast.h>
#include <NsCore/ReflectionHelper.h>
#include <NsCore/Log.h>
#include <NsCore/TypeClassCreator.h>
#include <NsCore/PlatformSettings.h>
#include <NsCore/CompilerSettings.h>
#include <NsCore/HighResTimer.h>
#include <NsCore/Category.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/Math.h>
#include <NsCore/Memory.h>
#include <NsCore/TypeEnumCreator.h>
#include <NsCore/BaseRefCounted.h>
#include <NsCore/CpuProfiler.h>
#include <NsCore/TypeCollection.h>
#include <NsCore/Ptr.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/TypeClassCreatorEmpty.h>
#include <NsCore/Init.h>
#include <NsCore/TypeMeta.h>
#include <NsCore/IdOf.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/Hash.h>
#include <NsCore/TypeClassBuilder.h>
#include <NsCore/Reflection.h>
#include <NsCore/UTF8.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Factory.h>
#include <NsCore/ValueHelper.h>
#include <NsCore/Atomic.h>

// Core/Nullable
#include <NsCore/Nullable.h>
#include <NsCore/NullableApi.h>

// Core/NSTL
#include <NsCore/VectorFwd.h>
#include <NsCore/HashMap.h>
#include <NsCore/ArrayRef.h>
#include <NsCore/StringFwd.h>
#include <NsCore/Pair.h>
#include <NsCore/Sort.h>
#include <NsCore/Vector.h>
#include <NsCore/String.h>

// Math/VectorMath
#include <NsMath/VectorMathApi.h>
#include <NsMath/Matrix.h>
#include <NsMath/AABBox.h>
#include <NsMath/Transform.h>
#include <NsMath/Vector.h>

// Core/TypeConverter
#include <NsCore/NullableConverter.h>
#include <NsCore/EnumConverter.h>
#include <NsCore/Converter.h>
#include <NsCore/StringConverter.h>
#include <NsCore/NumericConverter.h>
#include <NsCore/TypeConverter.h>
#include <NsCore/CharConverter.h>
#include <NsCore/TypeConverterApi.h>
#include <NsCore/SymbolConverter.h>

// Gui/DependencySystem
#include <NsGui/ValueStorageManagerImpl.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/DispatcherObject.h>
#include <NsGui/DependencySystemApi.h>
#include <NsGui/TypeConverterMetaData.h>
#include <NsGui/DependencyProperty.h>
#include <NsGui/ValueDestination.h>
#include <NsGui/FreezableEventReason.h>
#include <NsGui/INotifyPropertyChanged.h>
#include <NsGui/Freezable.h>
#include <NsGui/ProviderValue.h>
#include <NsGui/DependencyObjectValueData.h>
#include <NsGui/Expression.h>
#include <NsGui/DependencyData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/ISealable.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/ValueStorageManager.h>
#include <NsGui/ContentPropertyMetaData.h>

// Drawing/Types
#include <NsDrawing/Size.h>
#include <NsDrawing/TypesApi.h>
#include <NsDrawing/Point.h>
#include <NsDrawing/Color.h>
#include <NsDrawing/Thickness.h>
#include <NsDrawing/CornerRadius.h>
#include <NsDrawing/Rect.h>
#include <NsDrawing/SVGPath.h>

// Render/RenderDevice
#include <NsRender/RenderDeviceApi.h>
#include <NsRender/RenderDevice.h>
#include <NsRender/Texture.h>
#include <NsRender/RenderTarget.h>

// Gui/Providers
#include <NsGui/FontProvider.h>
#include <NsGui/MemoryStream.h>
#include <NsGui/XamlProvider.h>
#include <NsGui/ProvidersApi.h>
#include <NsGui/TextureProvider.h>
#include <NsGui/Stream.h>
#include <NsGui/FontProperties.h>
#include <NsGui/TextProperties.h>

// Gui/Core
#include <NsGui/ControlTemplate.h>
#include <NsGui/TickBar.h>
#include <NsGui/StatusBarItem.h>
#include <NsGui/CompositionUnderline.h>
#include <NsGui/RectangleGeometry.h>
#include <NsGui/ToolBarPanel.h>
#include <NsGui/EllipseGeometry.h>
#include <NsGui/GradientStopCollection.h>
#include <NsGui/IView.h>
#include <NsGui/ListBoxItem.h>
#include <NsGui/UIElement.h>
#include <NsGui/BindingListener.h>
#include <NsGui/Selector.h>
#include <NsGui/MultiDataTrigger.h>
#include <NsGui/MeshGeometry.h>
#include <NsGui/PathGeometry.h>
#include <NsGui/KeyboardNavigation.h>
#include <NsGui/IValueConverter.h>
#include <NsGui/ICollectionView.h>
#include <NsGui/IItemContainerGenerator.h>
#include <NsGui/TemplateBindingExtension.h>
#include <NsGui/Page.h>
#include <NsGui/GeometryGroup.h>
#include <NsGui/ProgressBar.h>
#include <NsGui/ConditionListener.h>
#include <NsGui/ResourceDictionary.h>
#include <NsGui/RoutedCommand.h>
#include <NsGui/UniformGrid.h>
#include <NsGui/Control.h>
#include <NsGui/TextBox.h>
#include <NsGui/BaseValueConverter.h>
#include <NsGui/INotifyDictionaryChanged.h>
#include <NsGui/Label.h>
#include <NsGui/BitmapSource.h>
#include <NsGui/TriggerAction.h>
#include <NsGui/NameScopePropertyMetaData.h>
#include <NsGui/CompositeTransform.h>
#include <NsGui/VirtualizingPanel.h>
#include <NsGui/BaseUICollection.h>
#include <NsGui/StackPanel.h>
#include <NsGui/DataTrigger.h>
#include <NsGui/ToolBarTray.h>
#include <NsGui/Bold.h>
#include <NsGui/Popup.h>
#include <NsGui/Text.h>
#include <NsGui/ToggleButton.h>
#include <NsGui/HeaderedItemsControl.h>
#include <NsGui/ApplicationCommands.h>
#include <NsGui/ItemContainerGenerator.h>
#include <NsGui/UpdateSourceTrigger.h>
#include <NsGui/PathSegment.h>
#include <NsGui/BaseDefinition.h>
#include <NsGui/Condition.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/TranslateTransform.h>
#include <NsGui/Style.h>
#include <NsGui/RenderOptions.h>
#include <NsGui/GroupBox.h>
#include <NsGui/FontFamily.h>
#include <NsGui/CollectionView.h>
#include <NsGui/DropShadowEffect.h>
#include <NsGui/MultiBindingExpression.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/ComponentCommands.h>
#include <NsGui/BaseButton.h>
#include <NsGui/ContentPresenter.h>
#include <NsGui/Path.h>
#include <NsGui/QuadraticBezierSegment.h>
#include <NsGui/BaseSetter.h>
#include <NsGui/CommandBinding.h>
#include <NsGui/ComboBox.h>
#include <NsGui/FocusManager.h>
#include <NsGui/FormattedText.h>
#include <NsGui/VirtualizationCacheLength.h>
#include <NsGui/TextBlock.h>
#include <NsGui/BulletDecorator.h>
#include <NsGui/Uri.h>
#include <NsGui/Italic.h>
#include <NsGui/BitmapImage.h>
#include <NsGui/Trigger.h>
#include <NsGui/BlurEffect.h>
#include <NsGui/MultiBinding.h>
#include <NsGui/ObservableCollection.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/ListBox.h>
#include <NsGui/Pen.h>
#include <NsGui/MatrixTransform.h>
#include <NsGui/BaseBinding.h>
#include <NsGui/HeaderedContentControl.h>
#include <NsGui/StreamGeometryContext.h>
#include <NsGui/TemplatePartMetaData.h>
#include <NsGui/CombinedGeometry.h>
#include <NsGui/VisualTreeHelper.h>
#include <NsGui/TextElement.h>
#include <NsGui/StatusBar.h>
#include <NsGui/ColumnDefinition.h>
#include <NsGui/CommandData.h>
#include <NsGui/VirtualizingStackPanel.h>
#include <NsGui/KeyBinding.h>
#include <NsGui/ImageSource.h>
#include <NsGui/InputEnums.h>
#include <NsGui/FrameworkTemplate.h>
#include <NsGui/LogicalTreeHelper.h>
#include <NsGui/Events.h>
#include <NsGui/IRenderer.h>
#include <NsGui/ContextMenu.h>
#include <NsGui/InlineUIContainer.h>
#include <NsGui/ValueTargetProvider.h>
#include <NsGui/Animatable.h>
#include <NsGui/BezierSegment.h>
#include <NsGui/UIElementEvents.h>
#include <NsGui/DataObject.h>
#include <NsGui/BaseCommand.h>
#include <NsGui/SizeChangedInfo.h>
#include <NsGui/DependsOnAttributeMetaData.h>
#include <NsGui/ContentControl.h>
#include <NsGui/PolyQuadraticBezierSegment.h>
#include <NsGui/ImageBrush.h>
#include <NsGui/BindingOperations.h>
#include <NsGui/KeyGesture.h>
#include <NsGui/Thumb.h>
#include <NsGui/ILayerManager.h>
#include <NsGui/ContextMenuService.h>
#include <NsGui/UIElementCollection.h>
#include <NsGui/IListIndexer.h>
#include <NsGui/Visual.h>
#include <NsGui/Colors.h>
#include <NsGui/BaseMenu.h>
#include <NsGui/ItemsPresenter.h>
#include <NsGui/Inline.h>
#include <NsGui/Shape.h>
#include <NsGui/ScaleTransform.h>
#include <NsGui/IDictionary.h>
#include <NsGui/TabControl.h>
#include <NsGui/PropertyPath.h>
#include <NsGui/IRecyclingItemContainerGenerator.h>
#include <NsGui/TreeViewItem.h>
#include <NsGui/IScrollInfo.h>
#include <NsGui/Grid.h>
#include <NsGui/CollectionViewSource.h>
#include <NsGui/IRenderProxyCreator.h>
#include <NsGui/LinearGradientBrush.h>
#include <NsGui/Brushes.h>
#include <NsGui/CheckBox.h>
#include <NsGui/BaseFreezableCollection.h>
#include <NsGui/LineSegment.h>
#include <NsGui/Mouse.h>
#include <NsGui/Enums.h>
#include <NsGui/ScrollContentPresenter.h>
#include <NsGui/UICollection.h>
#include <NsGui/BoxedFreezableCollection.h>
#include <NsGui/StreamGeometry.h>
#include <NsGui/ScrollBar.h>
#include <NsGui/VisualCollection.h>
#include <NsGui/InputBinding.h>
#include <NsGui/IMultiValueConverter.h>
#include <NsGui/Track.h>
#include <NsGui/BaseDictionary.h>
#include <NsGui/BaseTextBox.h>
#include <NsGui/IDictionaryIndexer.h>
#include <NsGui/Slider.h>
#include <NsGui/DrawingContext.h>
#include <NsGui/ItemCollection.h>
#include <NsGui/ItemsPanelTemplate.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/Element.h>
#include <NsGui/PolyLineSegment.h>
#include <NsGui/HierarchicalDataTemplate.h>
#include <NsGui/TabItem.h>
#include <NsGui/DataTemplateSelector.h>
#include <NsGui/PathFigure.h>
#include <NsGui/RowDefinition.h>
#include <NsGui/HandoffBehavior.h>
#include <NsGui/Panel.h>
#include <NsGui/TemplateBindingExpression.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/EventTrigger.h>
#include <NsGui/TileBrush.h>
#include <NsGui/Keyboard.h>
#include <NsGui/GradientBrush.h>
#include <NsGui/NameScope.h>
#include <NsGui/BaseBindingExpression.h>
#include <NsGui/ScrollViewer.h>
#include <NsGui/Separator.h>
#include <NsGui/ArcSegment.h>
#include <NsGui/LayerManager.h>
#include <NsGui/BaseObservableCollection.h>
#include <NsGui/Button.h>
#include <NsGui/Menu.h>
#include <NsGui/Transform.h>
#include <NsGui/Setter.h>
#include <NsGui/Viewbox.h>
#include <NsGui/Expander.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/WrapPanel.h>
#include <NsGui/DragDrop.h>
#include <NsGui/Hyperlink.h>
#include <NsGui/InputGesture.h>
#include <NsGui/ITimeManager.h>
#include <NsGui/UIElementData.h>
#include <NsGui/RadialGradientBrush.h>
#include <NsGui/PathExtensions.h>
#include <NsGui/UIPropertyMetadata.h>
#include <NsGui/IPropertyValueConverter.h>
#include <NsGui/ComboBoxItem.h>
#include <NsGui/TreeView.h>
#include <NsGui/TabPanel.h>
#include <NsGui/Decorator.h>
#include <NsGui/BaseCollection.h>
#include <NsGui/ToolTipService.h>
#include <NsGui/Line.h>
#include <NsGui/Span.h>
#include <NsGui/RoutedEvent.h>
#include <NsGui/VisualBrush.h>
#include <NsGui/ToolBar.h>
#include <NsGui/ItemsControl.h>
#include <NsGui/Effect.h>
#include <NsGui/Ellipse.h>
#include <NsGui/UserControl.h>
#include <NsGui/BindingExpression.h>
#include <NsGui/Run.h>
#include <NsGui/Transform3D.h>
#include <NsGui/Rectangle.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/RepeatButton.h>
#include <NsGui/Collection.h>
#include <NsGui/RoutedUICommand.h>
#include <NsGui/CommandManager.h>
#include <NsGui/Canvas.h>
#include <NsGui/ICommandSource.h>
#include <NsGui/IStoryboard.h>
#include <NsGui/AdornerDecorator.h>
#include <NsGui/ToolTip.h>
#include <NsGui/MultiTrigger.h>
#include <NsGui/Binding.h>
#include <NsGui/DockPanel.h>
#include <NsGui/BaseTrigger.h>
#include <NsGui/SkewTransform.h>
#include <NsGui/CoreApi.h>
#include <NsGui/GradientStop.h>
#include <NsGui/RangeBase.h>
#include <NsGui/ToolBarOverflowPanel.h>
#include <NsGui/RotateTransform.h>
#include <NsGui/Brush.h>
#include <NsGui/ICommand.h>
#include <NsGui/MarkupExtension.h>
#include <NsGui/TextureSource.h>
#include <NsGui/GridLength.h>
#include <NsGui/DashStyle.h>
#include <NsGui/RelativeSource.h>
#include <NsGui/BaseMultiValueConverter.h>
#include <NsGui/MatrixTransform3D.h>
#include <NsGui/INameScope.h>
#include <NsGui/Image.h>
#include <NsGui/PolyBezierSegment.h>
#include <NsGui/TransformGroup.h>
#include <NsGui/LineBreak.h>
#include <NsGui/LineGeometry.h>
#include <NsGui/MenuItem.h>
#include <NsGui/mscorlibTypes.h>
#include <NsGui/Border.h>
#include <NsGui/IList.h>
#include <NsGui/CompositeTransform3D.h>
#include <NsGui/Geometry.h>
#include <NsGui/RadioButton.h>
#include <NsGui/PasswordBox.h>
#include <NsGui/DataTemplate.h>
#include <NsGui/Underline.h>

// Gui/CachedFontProvider
#include <NsGui/CachedFontProviderApi.h>
#include <NsGui/CachedFontProvider.h>

// Gui/Controls
#include <NsGui/GridViewColumnHeader.h>
#include <NsGui/ListViewItem.h>
#include <NsGui/GridViewColumn.h>
#include <NsGui/ControlsApi.h>
#include <NsGui/GridViewRowPresenter.h>
#include <NsGui/ListView.h>
#include <NsGui/BaseGridViewRowPresenter.h>
#include <NsGui/GridView.h>
#include <NsGui/BaseView.h>
#include <NsGui/GridViewHeaderRowPresenter.h>

// Gui/Animation
#include <NsGui/PauseStoryboard.h>
#include <NsGui/LinearRectKeyFrame.h>
#include <NsGui/VisualTransition.h>
#include <NsGui/IEasingFunction.h>
#include <NsGui/ClockGroup.h>
#include <NsGui/ColorAnimationUsingKeyFrames.h>
#include <NsGui/SizeAnimation.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/Int32KeyFrame.h>
#include <NsGui/StopStoryboard.h>
#include <NsGui/DiscreteColorKeyFrame.h>
#include <NsGui/ObjectAnimationUsingKeyFrames.h>
#include <NsGui/Int16Animation.h>
#include <NsGui/MatrixAnimationUsingKeyFrames.h>
#include <NsGui/QuadraticEase.h>
#include <NsGui/ControllableStoryboardAction.h>
#include <NsGui/Duration.h>
#include <NsGui/DoubleAnimation.h>
#include <NsGui/LinearInt16KeyFrame.h>
#include <NsGui/SizeAnimationUsingKeyFrames.h>
#include <NsGui/PointAnimation.h>
#include <NsGui/TimelineGroup.h>
#include <NsGui/CircleEase.h>
#include <NsGui/DoubleAnimationUsingKeyFrames.h>
#include <NsGui/QuinticEase.h>
#include <NsGui/LinearDoubleKeyFrame.h>
#include <NsGui/VisualStateGroup.h>
#include <NsGui/Storyboard.h>
#include <NsGui/SplineSizeKeyFrame.h>
#include <NsGui/PointKeyFrame.h>
#include <NsGui/PointAnimationUsingKeyFrames.h>
#include <NsGui/Int16AnimationUsingKeyFrames.h>
#include <NsGui/EasingThicknessKeyFrame.h>
#include <NsGui/ColorKeyFrame.h>
#include <NsGui/ColorAnimation.h>
#include <NsGui/VisualStateManager.h>
#include <NsGui/DiscreteInt32KeyFrame.h>
#include <NsGui/EasingRectKeyFrame.h>
#include <NsGui/ThicknessAnimationUsingKeyFrames.h>
#include <NsGui/Int32Animation.h>
#include <NsGui/StringAnimationUsingKeyFrames.h>
#include <NsGui/DiscreteSizeKeyFrame.h>
#include <NsGui/QuarticEase.h>
#include <NsGui/StringKeyFrame.h>
#include <NsGui/DiscreteStringKeyFrame.h>
#include <NsGui/SizeKeyFrame.h>
#include <NsGui/SplineThicknessKeyFrame.h>
#include <NsGui/MatrixKeyFrame.h>
#include <NsGui/DiscretePointKeyFrame.h>
#include <NsGui/DiscreteMatrixKeyFrame.h>
#include <NsGui/DiscreteThicknessKeyFrame.h>
#include <NsGui/BeginStoryboard.h>
#include <NsGui/RectAnimationUsingKeyFrames.h>
#include <NsGui/SplineInt16KeyFrame.h>
#include <NsGui/Int32AnimationUsingKeyFrames.h>
#include <NsGui/AnimationTimeline.h>
#include <NsGui/SineEase.h>
#include <NsGui/EasingInt16KeyFrame.h>
#include <NsGui/RectKeyFrame.h>
#include <NsGui/EasingFunctionBase.h>
#include <NsGui/ObjectKeyFrame.h>
#include <NsGui/SplineInt32KeyFrame.h>
#include <NsGui/DiscreteRectKeyFrame.h>
#include <NsGui/DiscreteObjectKeyFrame.h>
#include <NsGui/EasingInt32KeyFrame.h>
#include <NsGui/ThicknessKeyFrame.h>
#include <NsGui/BaseAnimation.h>
#include <NsGui/ParallelTimeline.h>
#include <NsGui/DoubleKeyFrame.h>
#include <NsGui/DiscreteDoubleKeyFrame.h>
#include <NsGui/BooleanKeyFrame.h>
#include <NsGui/RepeatBehavior.h>
#include <NsGui/EasingSizeKeyFrame.h>
#include <NsGui/LinearColorKeyFrame.h>
#include <NsGui/ResumeStoryboard.h>
#include <NsGui/RectAnimation.h>
#include <NsGui/SplinePointKeyFrame.h>
#include <NsGui/BooleanAnimationUsingKeyFrames.h>
#include <NsGui/DiscreteInt16KeyFrame.h>
#include <NsGui/BounceEase.h>
#include <NsGui/EasingPointKeyFrame.h>
#include <NsGui/EasingColorKeyFrame.h>
#include <NsGui/DiscreteBooleanKeyFrame.h>
#include <NsGui/EasingDoubleKeyFrame.h>
#include <NsGui/SplineDoubleKeyFrame.h>
#include <NsGui/ThicknessAnimation.h>
#include <NsGui/AnimationClock.h>
#include <NsGui/LinearInt32KeyFrame.h>
#include <NsGui/BackEase.h>
#include <NsGui/LinearSizeKeyFrame.h>
#include <NsGui/SplineColorKeyFrame.h>
#include <NsGui/KeySpline.h>
#include <NsGui/BaseKeyFrame.h>
#include <NsGui/PowerEase.h>
#include <NsGui/SplineRectKeyFrame.h>
#include <NsGui/Timeline.h>
#include <NsGui/LinearPointKeyFrame.h>
#include <NsGui/Clock.h>
#include <NsGui/TimeSpan.h>
#include <NsGui/LinearThicknessKeyFrame.h>
#include <NsGui/CubicEase.h>
#include <NsGui/KeyTime.h>
#include <NsGui/Int16KeyFrame.h>
#include <NsGui/VisualState.h>
#include <NsGui/ExponentialEase.h>
#include <NsGui/ElasticEase.h>

#endif
